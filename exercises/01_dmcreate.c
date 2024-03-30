#include <petscdmplex.h>
#include <petscdmadaptor.h>
#include <petscsnes.h>
#include <petscds.h>
#include <petscviewerhdf5.h>

int main(int argc, char *argv[])
{
    DM dm;
    Vec vec;
    Mat mat;
    PetscFunctionBeginUser;
    PetscCall(PetscInitialize(&argc, &argv, NULL, __FILE__ "\n"));
    PetscCall(DMPlexCreate(PETSC_COMM_WORLD, &dm));
    PetscCall(DMCreateLocalVector(dm, &vec));
    PetscCall(DMCreateMatrix(dm, &mat));
    
    PetscCall(MatDestroy(&mat));
    PetscCall(VecDestroy(&vec));
    PetscCall(DMDestroy(&dm));
    PetscCall(PetscFinalize());
    return 0;
}
