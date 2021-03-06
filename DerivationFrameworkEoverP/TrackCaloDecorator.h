/* 
 * @file     TrackCaloDecorator.h
 * @author   Millie McDonald <emcdonal@cern.ch> // Main author
 * @author   Joakim Olsson <joakim.olsson@cern.ch> // Modifications and cross-checks
 * @brief    A derivation for ATLAS Run II E/p analyses. Extrapolates all tracks to calorimeter and decorates them with cluster and cell energies.
 * Updated: 2 December 2015, Millie McDonald
 * Updated: 12 December 2016, Joakim Olsson
 */
#ifndef __TRACKCALODECORATOR_H
#define __TRACKCALODECORATOR_H

#include <string>
#include <vector>

#include "TH1F.h"
#include "TTree.h"

#include "AthenaBaseComps/AthAlgTool.h"
#include "DerivationFrameworkInterfaces/IAugmentationTool.h"
#include "GaudiKernel/ToolHandle.h"
#include "GaudiKernel/ServiceHandle.h"
#include "GaudiKernel/ITHistSvc.h"
#include "CaloIdentifier/CaloCell_ID.h"
#include "RecoToolInterfaces/IParticleCaloExtensionTool.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODCaloEvent/CaloClusterChangeSignalState.h"

class TileTBID;
class ICaloSurfaceHelper;

namespace Trk {
  class IExtrapolator;
  class Surface;
  class TrackParametersIdHelper;
}
namespace DerivationFramework {

  class TrackCaloDecorator : public AthAlgTool, public IAugmentationTool {
    public: 
      TrackCaloDecorator(const std::string& t, const std::string& n, const IInterface* p);

      StatusCode initialize();
      StatusCode finalize();
      virtual StatusCode addBranches() const;

    private:

      std::string m_sgName;
      std::string m_eventInfoContainerName;
      std::string m_trackContainerName;
      std::string m_caloClusterContainerName;

      ToolHandle<Trk::IExtrapolator> m_extrapolator;
      ToolHandle<Trk::IParticleCaloExtensionTool> m_theTrackExtrapolatorTool;
      Trk::TrackParametersIdHelper* m_trackParametersIdHelper;
      ToolHandle<ICaloSurfaceHelper> m_surfaceHelper;

      const TileTBID* m_tileTBID; 

      bool m_doCutflow;

      // Tree with run number, event number, lumi block, and nTrks
      TTree* m_tree;
      int m_runNumber;
      int m_eventNumber;
      int m_lumiBlock;
      int m_nTrks;
      int m_nTrks_pass;

      // cutflows
      TH1F* m_cutflow_evt;
      TH1F* m_cutflow_trk;
      TH1F* m_ntrks_per_event_all;
      TH1F* m_ntrks_per_event_pass_all;
      int m_cutflow_evt_all;
      int m_cutflow_evt_pass_all;
      int m_cutflow_trk_all;
      int m_cutflow_trk_pass_extrapolation;
      int m_cutflow_trk_pass_cluster_matching;
      int m_cutflow_trk_pass_cell_matching;
      int m_cutflow_trk_pass_loop_matched_clusters;
      int m_cutflow_trk_pass_loop_matched_cells;
      int m_cutflow_trk_pass_all;

  }; 
} // Derivation Framework
#endif 
