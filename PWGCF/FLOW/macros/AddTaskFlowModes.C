///////////////////////////////////////////////////////////////////
//                                                               //
// AddTaskFlowModes                                              //
// Author: Naghmeh Mohammadi (nmohamma@cern.ch), Nikhef, 2017    //
//                                                               //
///////////////////////////////////////////////////////////////////
class AliAnalysisDataContainer;

AliAnalysisTaskFlowModes* AddTaskFlowModes(TString name = "name", 
					   Int_t PVtxZMax = 10,
					   Int_t NumTPCclsMin = 70,
					   Int_t TrackFilterBit = 96,
					   TString MultEstimator = "V0M",
					   Bool_t AntiProtonOnly = kFALSE,
					   Bool_t PIDbayesian = kFALSE,
                                           Double_t PIDprob = 0.9)
{
  cout<<"=========================================================="<<endl;
  cout<<"====================AddTaskFlowModes======================"<<endl;
  cout<<"=========================================================="<<endl;

  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) return 0x0;
  if (!mgr->GetInputEventHandler())	return 0x0;

  TString fileName = AliAnalysisManager::GetCommonFileName();   // by default, a file is open for writing. here, we get the filename
  fileName += Form(":%s",name.Data());      // create a subfolder in the file

  AliAnalysisTaskFlowModes* task1 = new AliAnalysisTaskFlowModes(name.Data()); // now we create an instance of your task
  if(!task1) return 0x0;

 // Analysis
    task1->SetRunMode(AliAnalysisTaskFlowModes::kFull);//kFull
    task1->SetNumEventsAnalyse(50);//In case of fRunMode == kTest it only analyses up to 50 events.  
    task1->SetAnalysisType(AliAnalysisTaskFlowModes::kAOD);
    task1->SetSampling(kFALSE);
    task1->SetFillQAhistos(kTRUE);
    task1->SetProcessCharged(kTRUE);
    task1->SetProcessPID(kTRUE,PIDbayesian);
    // Flow
    task1->SetFlowRFPsPtMin(0.2);
    task1->SetFlowRFPsPtMax(5.);
    // task1->SetFlowDoFourCorrelations(kFALSE);
    task1->SetFlowDoOnlyMixedCorrelations(kTRUE);
    task1->SetFlowFillWeights(kFALSE);
    task1->SetPositivelyChargedRef(kFALSE);//reference particles both positively charged
    task1->SetNegativelyChargedRef(kFALSE);//reference particles both negatively charged

    // task1->SetUseWeigthsFile("alice/cern.ch/user/v/vpacik/uniFlow_ver4_CENT_woSDD_16t_V0A/output/000267163/001/AnalysisResults.root");
    // task1->SetUseWeigthsFile("/alice/cern.ch/user/v/vpacik/weights_CENTwoSDD_16q.root");
    // Events selection
    task1->SetTrigger(0); // case 0: kINT7, case 1: kHighMultV0, case 2: kHighMultSPD.
    task1->SetMultEstimator(MultEstimator);//CL1, CL0
    task1->SetCentralityRange(kTRUE); // kTRUE: run from 0-100% kFALSE: run from 50-100%
    task1->SetPVtxZMax(PVtxZMax);
    // Charged selection
    task1->SetChargedEtaMax(0.8);
    // task1->SetChargedPtMin(0.2);
    // task1->SetChargedPtMax(5.);
    // task1->SetChargedDCAzMax(0.1);
    // task1->SetChargedDCAxyMax(0.2);
    task1->SetChargedNumTPCclsMin(NumTPCclsMin);
    task1->SetChargedTrackFilterBit(TrackFilterBit);
    // PID selection
    task1->SetPIDUseAntiProtonOnly(AntiProtonOnly);
    task1->SetPIDNumSigmasPionMax(3);
    task1->SetPIDNumSigmasKaonMax(3);
    task1->SetPIDNumSigmasProtonMax(3);
    if(PIDbayesian) task1->SetBayesianProbability(PIDprob);

  mgr->AddTask(task1); // add your task to the manager
  // Creating containers
  AliAnalysisDataContainer* cInput0 = mgr->GetCommonInputContainer();
  AliAnalysisDataContainer* cOutput1 = mgr->CreateContainer(Form("Flow_Refs_%s",name.Data()), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s",fileName.Data()));
  AliAnalysisDataContainer* cOutput2 = mgr->CreateContainer(Form("Flow_Charged_%s",name.Data()), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s",fileName.Data()));
  AliAnalysisDataContainer* cOutput3 = mgr->CreateContainer(Form("Flow_PID_%s",name.Data()), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s",fileName.Data()));
  AliAnalysisDataContainer* cOutput4 = mgr->CreateContainer(Form("QA_Events_%s",name.Data()), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s",fileName.Data()));
  AliAnalysisDataContainer* cOutput5 = mgr->CreateContainer(Form("QA_Charged_%s",name.Data()), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s",fileName.Data()));
  AliAnalysisDataContainer* cOutput6 = mgr->CreateContainer(Form("QA_PID_%s",name.Data()), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s",fileName.Data()));
  AliAnalysisDataContainer* cOutput7 = mgr->CreateContainer(Form("Flow_Weights_%s",name.Data()), TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s",fileName.Data()));

  // Connecting containers to task
  mgr->ConnectInput(task1,0,cInput0); // your task needs input: here we connect the manager to your task
  mgr->ConnectOutput(task1,1,cOutput1);
  mgr->ConnectOutput(task1,2,cOutput2);
  mgr->ConnectOutput(task1,3,cOutput3);
  mgr->ConnectOutput(task1,4,cOutput4);
  mgr->ConnectOutput(task1,5,cOutput5);
  mgr->ConnectOutput(task1,6,cOutput6);
  mgr->ConnectOutput(task1,7,cOutput7);

  return task1;
}