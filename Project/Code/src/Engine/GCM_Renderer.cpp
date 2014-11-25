#include "GCM_Renderer.h"
#include "GCM_MemoryUtils.h"
#include <iostream> //for memset


#include <sys/process.h>
#include <sysutil/sysutil_sysparam.h>
#include <cell/sysmodule.h>

#include <cell/gcm.h>

namespace Engine{
	namespace GCM{

		using namespace cell::Gcm;

		// The array of render surfaces.
		CellGcmSurface CGCM_Renderer::_surfaces[_numberOfSurfaces];
		// A reference to the current Fragment shader in use
		GCM_FragmentShader * CGCM_Renderer::_currentFrag;
		// A reference to the current Vertex shader in use
		GCM_VertexShader * CGCM_Renderer::_currentVert;
		// A reference to the default Fragment shader
		GCM_FragmentShader * CGCM_Renderer::defaultFrag;
		// A reference to the default Vertex shader
		GCM_VertexShader * CGCM_Renderer::defaultVert;

		CGCM_Renderer::CGCM_Renderer(){
			GCM_MemoryUtils::localHeapStart = 0;
			int err = 0;
			err = cellGcmInit(COMMAND_SIZE, BUFFER_SIZE, memalign(1024 * 1024, BUFFER_SIZE));
			ASSERT(err == CELL_OK);

			//InitDisplay();
			//InitSurfaces();
			//loadDefaultShaders();
		};

		CGCM_Renderer::~CGCM_Renderer(){};

		void CGCM_Renderer::renderMesh(Mesh*const msh, const Matrix4& mvp){}
		void CGCM_Renderer::DrawLine(const Vector3& p1, const Vector3& p2){}
		void CGCM_Renderer::DrawCross(const Vector3& p1, const float size){}
		void CGCM_Renderer::PrepFrame(){
			printf("Frame prep \n");

			cellGcmSetColorMask(CELL_GCM_COLOR_MASK_R |
				CELL_GCM_COLOR_MASK_G |
				CELL_GCM_COLOR_MASK_B |
				CELL_GCM_COLOR_MASK_A);

			cellGcmSetDepthTestEnable(CELL_GCM_TRUE);
			//cellGcmSetDepthTestEnable ( CELL_GCM_FALSE );

			cellGcmSetDepthFunc(CELL_GCM_LESS);
			//cellGcmSetDepthFunc(CELL_GCM_NEVER);

			cellGcmSetCullFaceEnable(CELL_GCM_FALSE);
			//cellGcmSetBlendEnable(CELL_GCM_FALSE);

			cellGcmSetShadeMode(CELL_GCM_SMOOTH);

			cellGcmSetBlendEnable(CELL_GCM_FALSE);

			// set polygon fill mode
			cellGcmSetFrontPolygonMode(CELL_GCM_POLYGON_MODE_FILL);

			//check for events
			//TODO: move this somewhere better
			cellSysutilCheckCallback();

			clearSurface();

		}
		void CGCM_Renderer::PostRender(){
			printf("Post render \n");
			ProcessLines();
			swapBuffers();
		}
		static float count = 0;
		void CGCM_Renderer::clearSurface(){
			printf("clear surface \n");
			//cellGcmSetClearColor((64 << 0) | (64 << 8) | (64 << 16) | (255 << 24));
			//cellGcmSetClearSurface(CELL_GCM_CLEAR_Z | CELL_GCM_CLEAR_S | CELL_GCM_CLEAR_R | CELL_GCM_CLEAR_G | CELL_GCM_CLEAR_B | CELL_GCM_CLEAR_A);
		
		count += 0.1f;
		unsigned char r = (sin((0.1f*count) + 0) * 127) + 128;
		unsigned char g = (sin((0.1f*count) + 2) * 127) + 128;
		unsigned char b = (sin((0.1f*count) + 4) * 127) + 128;
		cellGcmSetClearColor ((b <<0)|(g <<8)|(r <<16)|(255 <<24));

		cellGcmSetClearSurface (CELL_GCM_CLEAR_Z | CELL_GCM_CLEAR_S | CELL_GCM_CLEAR_R |
								CELL_GCM_CLEAR_G | CELL_GCM_CLEAR_B | CELL_GCM_CLEAR_A );
		}

		void CGCM_Renderer::assignShader(Mesh* m, std::string name){}

		//! Detect and set resolution
		void CGCM_Renderer::InitDisplay()
		{
			CellVideoOutState videoState;
			CellVideoOutResolution resolution;

			//Get the current display mode, 
			// This has to have been previously set in the target manager at some point
			int err = cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState);
			ASSERT(err == CELL_OK);

			err = cellVideoOutGetResolution(videoState.displayMode.resolutionId, &resolution);
			ASSERT(err == CELL_OK);

			printf("Output Resolution:\t%i x %i \n", resolution.width, resolution.height);
			screenWidth = resolution.width;
			screenHeight = resolution.height;

			//Rebuild a CellVideoOutConfiguration, using the current resolution
			uint32_t color_depth = 4; // ARGB8
			uint32_t z_depth = 4;     // COMPONENT24
			color_pitch = resolution.width*color_depth;
			color_size = color_pitch * resolution.height;
			depth_pitch = resolution.width*z_depth;
			depthSize = depth_pitch * resolution.height;

			CellVideoOutConfiguration video_cfg;
			//Fill videocfg with 0
			memset(&video_cfg, 0, sizeof(CellVideoOutConfiguration));

			video_cfg.resolutionId = videoState.displayMode.resolutionId;
			video_cfg.format = CELL_VIDEO_OUT_BUFFER_COLOR_FORMAT_X8R8G8B8;
			video_cfg.pitch = color_pitch;

			//Set the video configuration, we haven't changed anything other than possibly the Z/colour depth
			err = cellVideoOutConfigure(CELL_VIDEO_OUT_PRIMARY, &video_cfg, NULL, 0);
			ASSERT(err == CELL_OK);

			//Fetch videoState again, just to make sure everything went ok
			err = cellVideoOutGetState(CELL_VIDEO_OUT_PRIMARY, 0, &videoState);
			ASSERT(err == CELL_OK);

			//Store the aspect ratio
			switch (videoState.displayMode.aspect){
			case CELL_VIDEO_OUT_ASPECT_4_3:
				screenRatio = 4.0f / 3.0f;
				break;
			case CELL_VIDEO_OUT_ASPECT_16_9:
				screenRatio = 16.0f / 9.0f;
				break;
			default:
				printf("unknown aspect ratio %x\n", videoState.displayMode.aspect);
				screenRatio = 16.0f / 9.0f;
			}

			cellGcmSetFlipMode(CELL_GCM_DISPLAY_VSYNC);
			InitSurfaces();
		}

		//! Create Buffers/surfaces in memory
		void CGCM_Renderer::InitSurfaces(){
			printf("Creating buffers\n");

			//GCMconfig holds info regarding memory and clock speeds
			CellGcmConfig config;
			cellGcmGetConfiguration(&config);

			//Get the base address of the mapped RSX local memory 
			GCM_MemoryUtils::localHeapStart = (uint32_t)config.localAddress;

			//Allocate a 64byte aligned segment of RSX memory that is the size of a depth buffer
			void * depthBuffer = GCM_MemoryUtils::localMemoryAlign(64, depthSize);
			uint32_t depthOffset;

			/* cellGcmAddressToOffset converts an effective address in the area accessible by the RSX to an offset value.
			An offset is the space between from the base address of local memory and a certain useable address.
			Offsets are used in gcm commands that deal with shader parameters, texture mapping and vertex arrays.
			They serve no real use other than as a parameter for these functions.
			*/

			//The offset value will be stored into depthOffset.
			cellGcmAddressToOffset(depthBuffer, &depthOffset);

			for (int i = 0; i < _numberOfSurfaces; ++i)
			{
				///Allocate a 64byte aligned segment of RSX memory that is the size of a colour buffer
				void *buffer = GCM_MemoryUtils::localMemoryAlign(64, color_size);

				//Get the offset address for it and store it in surfaces[i].colorOffset [0]		
				cellGcmAddressToOffset(buffer, &_surfaces[i].colorOffset[0]);

				/* This function registers a buffer that outputs to a display.
				This is the point where the buffer is actually written to local memory.
				Parameters:
				cellGcmSetDisplayBuffer ( Buffer ID (0 - 7), memory offset, pitch - Horizontal byte width,
				width - Horizontal resolution (number of pixels), height - Vertical resolution(number of pixels)
				*/
				cellGcmSetDisplayBuffer(i, _surfaces[i].colorOffset[0], color_pitch, screenWidth, screenHeight);

				// Now we set other parameters on each CellGcmSurface object

				//whether to place the color buffer, main memory or local memory.
				_surfaces[i].colorLocation[0] = CELL_GCM_LOCATION_LOCAL;
				//Pitch size of the color buffer (resolution.width*color_depth)
				_surfaces[i].colorPitch[0] = color_pitch;
				//Target of the color buffer    
				_surfaces[i].colorTarget = CELL_GCM_SURFACE_TARGET_0;

				//Init the color buffers
				//Up to 4 color buffers can be used on a CellGcmSurface, but we only use 1.
				for (int j = 1; j < 4; ++j)
				{
					_surfaces[i].colorLocation[j] = CELL_GCM_LOCATION_LOCAL;
					_surfaces[i].colorOffset[j] = 0;
					_surfaces[i].colorPitch[j] = 64;
				}

				//Type of render target (Pitch or swizzle)
				_surfaces[i].type = CELL_GCM_SURFACE_PITCH;
				//Antialiasing format type (None in this case)
				_surfaces[i].antialias = CELL_GCM_SURFACE_CENTER_1;
				//Format of the color buffer
				_surfaces[i].colorFormat = CELL_GCM_SURFACE_A8R8G8B8;
				//Format of the depth and stencil buffers (16-bit depth or 24-bit depth and 8-bit stencil)
				_surfaces[i].depthFormat = CELL_GCM_SURFACE_Z24S8;
				//whether to place the depth buffer, main memory or local memory.
				_surfaces[i].depthLocation = CELL_GCM_LOCATION_LOCAL;
				//The offset address to our depth buffer (We only need 1 for both surfaces)
				_surfaces[i].depthOffset = depthOffset;
				//Pitch size of the depth buffer (resolution.width*z_depth)
				_surfaces[i].depthPitch = depth_pitch;
				//Dimensions (in pixels)
				_surfaces[i].width = screenWidth;
				_surfaces[i].height = screenHeight;
				//Window offsets
				_surfaces[i].x = 0;
				_surfaces[i].y = 0;
			}


			/*
			The surfaces[] array contains CellGcmSurface objects and is in stack memory somewhere,
			and a bunch of new buffer objects have just been created and stored in RSX Local Memory.
			Each CellGcmSurface object has a pointer to its corresponding buffer in .colorOffset [0].
			When we call cellGcmSetSurface(), we pass it an CellGcmSurface from our array,
			The parameters that we set on that object will be read, processed and passed to the RSX.
			*/

			//Set Surface[0] to be the first surface to render to
			cellGcmSetSurface(&_surfaces[0]);
			//Used to keep track of the surface currently being rendered to.
			_swapFlag = false;
		}

		void CGCM_Renderer::loadDefaultShaders(){}

		//! Switch which buffer is active(being rendered on) and currentyl displayed
		void CGCM_Renderer::swapBuffers(){
			printf("Swap \n"); 
			//non-zero indicates hardware is still  processing the last flip
			while (cellGcmGetFlipStatus() != 0)
			{
				sys_timer_usleep(300);
			}

			//reset flips status
			cellGcmResetFlipStatus();

			//flip
			cellGcmSetFlip((uint8_t)_swapFlag);

			//flush the pipline
			cellGcmFlush();
			cellGcmSetWaitFlip();

			//Toggle the swapvalue flag
			_swapFlag = !_swapFlag;

			//Tell gcm to render into the correct surface
			//TODO: make this suitable for more than 2 surfaces.
			cellGcmSetSurface(&_surfaces[_swapFlag]);
		}

		//! Set the active vertex and fragment shader
		void CGCM_Renderer::SetCurrentShader(GCM_VertexShader & vert, GCM_FragmentShader & frag){}

		//! Initialises viewport (coordinate scaling)
		void CGCM_Renderer::SetViewport(){}

		void CGCM_Renderer::Shutdown(){}

	
	}
}