
AliAnalysisTaskHaHFECorrel * ConfigHaHFECorrel(Int_t period, Double_t MinPtEvent, Double_t MaxPtEvent, Bool_t TRDQA, Bool_t TagEff, Bool_t RecEff, Bool_t CorrHadron, Bool_t CorrLP, Bool_t MCTruth,  Bool_t IsMC,Bool_t IsAOD, Bool_t UseTender, Double_t EtaMax, Int_t ITSnCut, Float_t ITSSharedCluster, Int_t TPCnCut, Int_t TPCnCutdEdx, Double_t PhotElecPtCut, Int_t PhotElecTPCnCut, Bool_t PhotElecITSrefitCut, Int_t PhotCorrCase, Double_t InvmassCut, Int_t HTPCnCut,Bool_t HITSrefitCut, Bool_t HTPCrefitCut,Bool_t UseITS, Double_t SigmaITScut, Double_t SigmaTOFcut, Double_t SigmaTPCcut, const char * ID="")
{

  //AliHFEcuts *hfecuts = new AliHFECuts("name", "title");
  //hfecuts->

  TString Name;
  Name = "HaHFECorrel_";
  Name+=ID;
  AliAnalysisTaskHaHFECorrel *task = new AliAnalysisTaskHaHFECorrel(Name);
  printf("task ------------------------ %p\n ", task);
  task->SetPeriod(period);
  printf("\nRunning over period %i", period);
  task->SetHadronCorrelation(CorrHadron);

  if (MinPtEvent>0.1 || MaxPtEvent<100) {
    printf("\nEventBias by momentum selection: ptMin: %f, ptMax: %f", MinPtEvent, MaxPtEvent);
    task->SetPtMinEvent(MinPtEvent);
    task->SetPtMaxEvent(MaxPtEvent);
  }


  if (TRDQA) printf("\nPerforming TRDQA");
  task->SetTRDQA(TRDQA);
  if (TagEff) printf ("\nGenerate TagEff Histograms");
  task->SetTagEff(TagEff);
  if (RecEff) printf ("\nGenerate RecEff histograms");
  task->SetRecEff(RecEff);
  if (CorrHadron) printf("\nCorrelating Hadrons");
  task->SetHadronCorrelation(CorrHadron);
  if (CorrLP) printf("\nCorrelating LP");
  task->SetLPCorrelation(CorrLP);
  if (MCTruth) printf("\nCorrelating MCTruh");
  task->SetMCTruthCorrelation(MCTruth);

  task->SetMC(IsMC);
  printf("\nIs MC? %i", IsMC);
  task->SetAODanalysis(IsAOD);
  printf("\nIs AOD? %i", IsAOD);
  task->SetTender(UseTender);
  printf("\nUse Tender? %i", UseTender);
 
  task->SetEtaMax(EtaMax);
  printf("\nElectron |EtaMax| %f", EtaMax);

  task->SetITSnCut(ITSnCut);
  printf("\nElectron ITSNclsCut: %i", ITSnCut);

  task->SetITSSharedClusterCut(ITSSharedCluster);
  printf("\nElectron ITSSharedClusterCut: %f", ITSSharedCluster); 

  task->SetTPCnCut(TPCnCut);
  printf("\nElectron TPCNclsCut: %i", TPCnCut);

  task->SetTPCnCutdEdx(TPCnCutdEdx);
  printf("\nElectron TPCNclsdEdxCut: %i", TPCnCutdEdx);

  task->SetPhotElecPtCut(PhotElecPtCut);
  printf("\nPhotElec PtCut: %f", PhotElecPtCut);

  task->SetPhotElecTPCnCut(PhotElecTPCnCut);
  printf("\nPhotElec TPCNclsCut: %i", PhotElecTPCnCut);
  
  task->SetPhotElecITSrefitCut(PhotElecITSrefitCut);
  printf("\nPhotElec ITSrefit? %i", PhotElecITSrefitCut);

  task->SetPhotCorrCase(PhotCorrCase);
  printf("\nPhotCorrCase? %i", PhotCorrCase);

  task->SetInvmassCut(InvmassCut);
  printf("\nInvMass Cut: %f", InvmassCut);

  task->SetHTPCnCut(HTPCnCut);
  printf("\nHadron TPCNclsCut: %i", HTPCnCut);

  task->SetHITSrefitCut(HITSrefitCut);
  printf("\nHadron ITSrefit? %i", HITSrefitCut);

  task->SetHTPCrefitCut(HTPCrefitCut);
  printf("\nHadron TPCrefit? %i", HTPCrefitCut);

 
  task->SetUseITS(UseITS);
  printf("\nUse ITS? %i", UseITS);
  task->SetSigmaITScut(SigmaITScut);
  printf("\nITS nSigma: %f", SigmaITScut);
  task->SetSigmaTOFcut(SigmaTOFcut);
  printf("\nTOF nSigma: %f", SigmaTOFcut);
  task->SetSigmaTPCcut(SigmaTPCcut);
  printf("\nTPC nSigma min: %f\n", SigmaTPCcut);


  // task->SetOpeningAngleCut(OpeningAngleCut);
 // task->SetHFECuts(hfecuts);

  // Define PID
  //AliHFEpid *pid = task->GetPID();
  //if(useMC) pid->SetHasMCData(kTRUE);

  printf("*************************************\n");
  printf("Configuring standard Task:\n");
  //printf("MC is %i", IsMC);
  //task->PrintStatus();
  //pid->PrintStatus();
  printf("*************************************\n"); 
  return task;
}
