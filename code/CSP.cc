// Constraint satisfaction problems

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define DONE   -1
#define FAILED -2

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;

typedef set<int> SI;

// Lists of assigned/unassigned variables.
VI assigned_vars;
SI unassigned_vars;

// For each variable, a list of reductions (each of which a list of eliminated
// variables)
VVVI reductions;

// For each variable, a list of the variables whose domains it reduced in
// forward-checking.
VVI forward_mods;

// need to implement ----------------------------
int Value(int var);

void SetValue(int var, int value);
void ClearValue(int var);

int DomainSize(int var);
void ResetDomain(int var);
void AddValue(int var, int value);
void RemoveValue(int var, int value);

int NextVar() {
  if ( unassigned_vars.empty() ) return DONE;
  
  // could also do most constrained...
  int var = *unassigned_vars.begin();
  return var;
}

int Initialize() {
  // setup here
  return NextVar();
}
// ------------------------- end -- need to implement


void UpdateCurrentDomain(int var) {
  ResetDomain(var);
  for (int i = 0; i < reductions[var].size(); i++) {
    vector<int>& red = reductions[var][i];
    for (int j = 0; j < red.size(); j++) {
      RemoveValue(var, red[j]);
    }
  }
}


void UndoReductions(int var) {
  for (int i = 0; i < forward_mods[var].size(); i++) {
    int other_var = forward_mods[var][i];
    VI& red = reductions[other_var].back();
    for (int j = 0; j < red.size(); j++) {
      AddValue(other_var, red[j]);
    }
    reductions[other_var].pop_back();
  }
  forward_mods[var].clear();
}


bool ForwardCheck(int var, int other_var) {
  vector<int> red;
  
  foreach value in current_domain(other_var) {
    SetValue(other_var, value);
    if ( !Consistent(var, other_var) ) {
      red.push_back(value);
      RemoveValue(other_var, value);
    }
    ClearValue(other_var);
  }
  if ( !red.empty() ) {
    reductions[other_var].push_back(red);
    forward_mods[var].push_back(other_var);
  }
  
  return DomainSize(other_var) != 0;
}


pair<int, bool> Unlabel(int var) {
  assigned_vars.pop_back();
  unassigned_vars.insert(var);
  
  UndoReductions(var);
  UpdateCurrentDomain(var);
  
  if ( assigned_vars.empty() ) return make_pair(FAILED, true);
  
  int prev_var = assigned_vars.back();
  RemoveValue(prev_var, Value(prev_var));
  ClearValue(prev_var);
  if ( DomainSize(prev_var) == 0 ) {
    return make_pair(prev_var, false);
  } else {
    return make_pair(prev_var, true);
  }
}


pair<int, bool> Label(int var) {
  unassigned_vars.erase(var);
  assigned_vars.push_back(var);
  
  bool consistent;
  foreach value in current_domain(var) {
    SetValue(var, value);
    consistent = true;
    for (int j=0; j<unassigned_vars.size(); j++) {
      int other_var = unassigned_vars[j];
      if ( !ForwardCheck(var, other_var) ) {
        RemoveValue(var, value);
        consistent = false;
        UndoReductions(var);
        ClearValue(var);
        break;
      }
    }
    if ( consistent ) return (NextVar(), true);
  }
  return make_pair(var, false);
}



void BacktrackSearch(int num_var) {
  // (next variable to mess with, whether current state is consistent)
  pair<int, bool> var_consistent = make_pair(Initialize(), true);
  while ( true ) {
    if ( var_consistent.second ) var_consistent = Label(var_consistent.first);
    else var_consistent = Unlabel(var_consistent.first);
    
    if ( var_consistent.first == DONE ) return; // solution found
    if ( var_consistent.first == FAILED ) return; // no solution
  }
}
