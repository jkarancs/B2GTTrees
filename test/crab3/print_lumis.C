void print_lumis(std::string files) {
  TChain* c = new TChain("c");
  c->Add((files+"/B2GTTreeMaker/B2GTree").c_str());
  unsigned int run, ls;
  std::map<unsigned long, bool> already_printed;
  c->SetBranchAddress("evt_RunNumber", &run);
  c->SetBranchAddress("evt_LumiBlock", &ls);
  for (Long64_t i = 0, n = c->GetEntries(); i<n; ++i) {
    c->GetEntry(i);
    unsigned long runls = run*100000 + ls;
    if (!already_printed.count(runls)) {
      std::cout<<"RUN/LS: "<<run<<" "<<ls<<std::endl;
      already_printed[runls] = 1;
    }
  }
  gApplication->Terminate();
}
