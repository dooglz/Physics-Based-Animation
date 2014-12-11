// Creates and manages the spacial partition, also used for returning a list of
// near objects
#include "SpacePartition.h"
#include "Physics_Object.h"
#include "../Engine/Maths.h"

namespace Physics {

#if (DIMENSTIONS == 2)
std::vector<CPhysicsObject*>* CSpacePartition::_theGrid[LENGTH][LENGTH];
#elif(DIMENSTIONS == 3)
std::vector<CPhysicsObject*>* CSpacePartition::_theGrid[LENGTH][LENGTH][LENGTH];
#endif

void CSpacePartition::Remove(const CPhysicsObject& obj) {}

void CSpacePartition::Update() {
  std::vector<CPhysicsObject*>* box;
  unsigned int X, Z;
  for (unsigned int i = 0; i < LENGTH; i++) {
    for (unsigned int j = 0; j < LENGTH; j++) {
      box = _theGrid[i][j];
      if (box == NULL) {
        continue;
      }

      for (unsigned int l = 0; l < box->size(); l++) {
        getSpace((*box)[l]->GetPosition(), X, Z, X);
        if (X != i || Z != j) {
          // moved
          if (_theGrid[X][Z] == NULL) {
            _theGrid[X][Z] = new std::vector<CPhysicsObject*>();
          }
          // add to new box
          _theGrid[X][Z]->push_back((*box)[l]);
          // remove from this box
          box->erase(box->begin() + l);
          l--;
        }
      }
    }
  }
}

void CSpacePartition::Register(CPhysicsObject* const obj) {
  std::vector<CPhysicsObject*>* space = getSpace(obj->GetPosition());
  space->push_back(obj);
}

void CSpacePartition::getSpace(const Vector3& Position, unsigned int& X,
                               unsigned int& Z, unsigned int& Y) {
  if (abs(Position.getX()) > (WORLDSIZE / 2.0f) ||
      abs(Position.getZ()) > (WORLDSIZE / 2.0f) ||
      (DIMENSTIONS == 3 && abs(Position.getY()) > (WORLDSIZE))) {
    // out of bounds
    printf("OUT OF BOUNDS!");
    ASSERT(false);
  }
  // not quite right, as we count from 0.
  X = (unsigned int)ceil((Position.getX() - ORIGIN.getX()) / BOXSIZE);
  Z = (unsigned int)ceil((Position.getZ() - ORIGIN.getZ()) / BOXSIZE);
#if (DIMENSTIONS == 3)
  Y = (unsigned int)ceil((Position.getY() - ORIGIN.getY()) / BOXSIZE);
#endif
}

std::vector<CPhysicsObject*>* CSpacePartition::getSpace(
    const Vector3& Position) {
  unsigned int X, Z;
#if (DIMENSTIONS == 3)
  unsigned int Y;
  getSpace(Position, X, Y, Z) return _theGrid[X][Z][Y];
#elif(DIMENSTIONS == 2)
  getSpace(Position, X, Z, X);
  if (_theGrid[X][Z] == NULL) {
    _theGrid[X][Z] = new std::vector<CPhysicsObject*>();
  }
  return _theGrid[X][Z];
#endif
}

std::vector<CPhysicsObject*>** CSpacePartition::getSurroundingSpaces(
    const Vector3& Position) {
  unsigned int X, Z;

#if (DIMENSTIONS == 3)
  unsigned int Y;

  std::vector<CPhysicsObject*>* neigbours[27];
  getSpace(Position, X, Y, Z);
  neigbours[0] = _theGrid[X][Z][Y - 1];
  neigbours[1] = _theGrid[X - 1][Z - 1][Y - 1];
  neigbours[2] = _theGrid[X - 1][Z][Y - 1];
  neigbours[3] = _theGrid[X - 1][Z + 1][Y - 1];
  neigbours[4] = _theGrid[X][Z - 1][Y - 1];
  neigbours[5] = _theGrid[X][Z + 1][Y - 1];
  neigbours[6] = _theGrid[X + 1][Z - 1][Y - 1];
  neigbours[7] = _theGrid[X + 1][Z][Y - 1];
  neigbours[8] = _theGrid[X + 1][Z + 1][Y - 1];

  neigbours[0] = _theGrid[X][Z][Y];
  neigbours[1] = _theGrid[X - 1][Z - 1][Y];
  neigbours[2] = _theGrid[X - 1][Z][Y];
  neigbours[3] = _theGrid[X - 1][Z + 1][Y];
  neigbours[4] = _theGrid[X][Z - 1][Y];
  neigbours[5] = _theGrid[X][Z + 1][Y];
  neigbours[6] = _theGrid[X + 1][Z - 1][Y];
  neigbours[7] = _theGrid[X + 1][Z][Y];
  neigbours[8] = _theGrid[X + 1][Z + 1][Y];

  neigbours[0] = _theGrid[X][Z][Y + 1];
  neigbours[1] = _theGrid[X - 1][Z - 1][Y + 1];
  neigbours[2] = _theGrid[X - 1][Z][Y + 1];
  neigbours[3] = _theGrid[X - 1][Z + 1][Y + 1];
  neigbours[4] = _theGrid[X][Z - 1][Y + 1];
  neigbours[5] = _theGrid[X][Z + 1][Y + 1];
  neigbours[6] = _theGrid[X + 1][Z - 1][Y + 1];
  neigbours[7] = _theGrid[X + 1][Z][Y + 1];
  neigbours[8] = _theGrid[X + 1][Z + 1][Y + 1];

  return neigbours;

#elif(DIMENSTIONS == 2)
  std::vector<CPhysicsObject*>** neigbours =
      new std::vector<CPhysicsObject*>* [9];
  getSpace(Position, X, Z, X);

  if (X >= LENGTH - 1) {
    X = LENGTH - 2;
  }
  if (Z >= LENGTH - 1) {
    Z = LENGTH - 2;
  }
  if (X <= 0) {
    X = 1;
  }
  if (Z <= 0) {
    Z = 1;
  }

  // printf("%i - X - %i, Z - %i\n",LENGTH, X, Z);

  if (_theGrid[X][Z] == NULL) {
    _theGrid[X][Z] = new std::vector<CPhysicsObject*>();
  }
  neigbours[0] = _theGrid[X][Z];
  if (_theGrid[X - 1][Z - 1] == NULL) {
    _theGrid[X - 1][Z - 1] = new std::vector<CPhysicsObject*>();
  }
  neigbours[1] = _theGrid[X - 1][Z - 1];
  if (_theGrid[X - 1][Z] == NULL) {
    _theGrid[X - 1][Z] = new std::vector<CPhysicsObject*>();
  }
  neigbours[2] = _theGrid[X - 1][Z];
  if (_theGrid[X - 1][Z + 1] == NULL) {
    _theGrid[X - 1][Z + 1] = new std::vector<CPhysicsObject*>();
  }
  neigbours[3] = _theGrid[X - 1][Z + 1];
  if (_theGrid[X][Z - 1] == NULL) {
    _theGrid[X][Z - 1] = new std::vector<CPhysicsObject*>();
  }
  neigbours[4] = _theGrid[X][Z - 1];
  if (_theGrid[X][Z + 1] == NULL) {
    _theGrid[X][Z + 1] = new std::vector<CPhysicsObject*>();
  }
  neigbours[5] = _theGrid[X][Z + 1];
  if (_theGrid[X + 1][Z - 1] == NULL) {
    _theGrid[X + 1][Z - 1] = new std::vector<CPhysicsObject*>();
  }
  neigbours[6] = _theGrid[X + 1][Z - 1];
  if (_theGrid[X + 1][Z] == NULL) {
    _theGrid[X + 1][Z] = new std::vector<CPhysicsObject*>();
  }
  neigbours[7] = _theGrid[X + 1][Z];
  if (_theGrid[X + 1][Z + 1] == NULL) {
    _theGrid[X + 1][Z + 1] = new std::vector<CPhysicsObject*>();
  }
  neigbours[8] = _theGrid[X + 1][Z + 1];
  return neigbours;
#endif
}
}