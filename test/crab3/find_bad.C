void find_bad(std::string files) {
  TChain* c = new TChain("c");
  c->Add((files+"/B2GTTreeMaker/B2GTree").c_str());
  unsigned int run, ls;
  std::map<std::string, bool> already_printed;
  c->SetBranchAddress("evt_RunNumber", &run);
  for (Long64_t i = 0, n = c->GetEntries(); i<n; i+=10000) {
    c->GetEntry(i);
    std::string name = c->GetFile()->GetName();
    if (!already_printed.count(name)) {
      std::cout<<"testing file: "<<name<<std::endl;
      already_printed[name] = 1;
    }
  }
  gApplication->Terminate();
}
