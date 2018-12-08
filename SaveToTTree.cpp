
#include "Count.h"
#include "FiberInfo.h"
#include <TFile.h>
#include <TTree.h>

void SaveToTTree(std::vector<FiberInfo> &infos)
{
    FiberInfo *info = new FiberInfo();

    TFile file{"fiber.root", "recreate"};
    TTree fibertree{"fibertree", "Fiber in TTree"};
    fibertree.Branch("x", &info->x, "x/I");
    fibertree.Branch("y", &info->y, "y/I");
    fibertree.Branch("num_pixel", &info->num_pixel, "num_pixel/I");
    fibertree.Branch("avg_x", &info->avg_x, "avg_x/F");
    fibertree.Branch("avg_y", &info->avg_y, "avg_y/F");
    fibertree.Branch("avg_clr", &info->avg_clr, "avg_clr/F");

    for(int i = 0; i < infos.size(); ++i)
    {
        *info = infos[i];
        fibertree.Fill();
    }

    fibertree.Write();

    TTree fiberobjtree{"fiberobjtree", "Fiber Object in TTree"};
    fiberobjtree.Branch("fiber", &info, 16000, 0);
    for(int i = 0; i < infos.size(); ++i)
    {
        *info = infos[i];
        fiberobjtree.Fill();
    }

    fiberobjtree.Write();
}

