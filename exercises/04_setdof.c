#include <petscdmplex.h>
#include <petscdmadaptor.h>
#include <petscsnes.h>
#include <petscds.h>
#include <petscviewerhdf5.h>

PetscErrorCode SetTestCones(DM dm)
// https://petsc.org/release/manual/dmplex/
{
    PetscFunctionBeginUser;
    PetscCall(DMSetDimension(dm, 2)); // https://petsc.org/release/manual/vec/#dmda-creating-vectors-for-structured-grids
    PetscCall(DMPlexSetChart(dm, 0, 11));
    /* DMPlexSetConeSize(dm, point, number of points that cover the point); */
    PetscCall(DMPlexSetConeSize(dm, 0, 3));
    PetscCall(DMPlexSetConeSize(dm, 1, 3));
    PetscCall(DMPlexSetConeSize(dm, 6, 2));
    PetscCall(DMPlexSetConeSize(dm, 7, 2));
    PetscCall(DMPlexSetConeSize(dm, 8, 2));
    PetscCall(DMPlexSetConeSize(dm, 9, 2));
    PetscCall(DMPlexSetConeSize(dm, 10, 2));
    PetscCall(DMSetUp(dm));

    /* DMPlexSetCone(dm, point, [points that cover the point]); */
    PetscInt cone0[] = {6,7,8};
    PetscCall(DMPlexSetCone(dm, 0, cone0));
    cone0[0] = 7; cone0[1] = 9; cone0[2] = 10;
    PetscCall(DMPlexSetCone(dm, 1, cone0));
    cone0[0] = 2; cone0[1] = 3;
    PetscCall(DMPlexSetCone(dm, 6, cone0));
    cone0[0] = 3; cone0[1] = 4;
    PetscCall(DMPlexSetCone(dm, 7, cone0));
    cone0[0] = 4; cone0[1] = 2;
    PetscCall(DMPlexSetCone(dm, 8, cone0));
    cone0[0] = 4; cone0[1] = 5;
    PetscCall(DMPlexSetCone(dm, 9, cone0));
    cone0[0] = 5; cone0[1] = 3;
    PetscCall(DMPlexSetCone(dm, 10, cone0));
    PetscCall(DMPlexSymmetrize(dm));
    PetscCall(DMPlexStratify(dm));

    PetscFunctionReturn(PETSC_SUCCESS);
}



int main(int argc, char *argv[])
{
    DM dm;
    PetscFunctionBeginUser;
    PetscCall(PetscInitialize(&argc, &argv, NULL, __FILE__ "\n"));
    PetscCall(DMPlexCreate(PETSC_COMM_WORLD, &dm));

    PetscCall(SetTestCones(dm));

    PetscViewer viewer = PETSC_VIEWER_STDOUT_WORLD;
//    PetscCall(PetscViewerDrawOpen(PETSC_COMM_WORLD, 0, "", 300, 0, 300, 300, &viewer));
    PetscCall(DMView(dm, viewer));
    PetscCall(DMPlexTopologyView(dm, viewer));
    PetscCall(DMPlexCoordinatesView(dm, viewer));
    PetscCall(DMPlexLabelsView(dm, viewer));

    PetscSection s;
    PetscCall(DMGetSection(dm, &s));

// https://petsc.org/release/manual/dmplex/#data-layout-by-hand
    PetscInt pStart, pEnd, cStart, cEnd, c, vStart, vEnd, v, eStart, eEnd, e;

    PetscCall(DMPlexGetChart(dm, &pStart, &pEnd));
    PetscCall(DMPlexGetHeightStratum(dm, 0, &cStart, &cEnd));   // cells
    PetscCall(DMPlexGetHeightStratum(dm, 1, &eStart, &eEnd));   // edges
    PetscCall(DMPlexGetHeightStratum(dm, 2, &vStart, &vEnd));   // vertices, equivalent to DMPlexGetDepthStratum(dm, 0, &vStart, &vEnd);
    PetscCall(PetscSectionSetChart(s, pStart, pEnd));
    for(c = cStart; c < cEnd; ++c)
        PetscCall(PetscSectionSetDof(s, c, 1));
    for(v = vStart; v < vEnd; ++v)
        PetscCall(PetscSectionSetDof(s, v, 1));
    for(e = eStart; e < eEnd; ++e)
        PetscCall(PetscSectionSetDof(s, e, 2)); // two dof on each edge
    PetscCall(PetscSectionSetUp(s));

#define VALOUT(val) PetscCall(PetscPrintf(PETSC_COMM_WORLD, #val ": %d\n", val))
    VALOUT(pStart);
    VALOUT(pEnd);
    VALOUT(cStart);
    VALOUT(cEnd);
    VALOUT(vStart);
    VALOUT(vEnd);
    VALOUT(eStart);
    VALOUT(eEnd);

    // Destroy
//    PetscCall(PetscViewerDestroy(&viewer));
    PetscCall(DMDestroy(&dm));
    PetscCall(PetscFinalize());
    return 0;
}
