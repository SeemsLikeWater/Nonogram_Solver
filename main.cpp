#include "grid.h"

//this code includes some precheck, to guess some easy cells. 
//If you want to check with logic, set the "return 0;" on line 11
//to "return 1;"



//POST: returns 1 if the program shall operate with logic, and 0, if only brut force shall be used
bool logic_test(){
  return 1; 
}


//an '!' marks a guaranteed filled cell, and an 'x' marks a guaranteed empty cell
//they will be replaced with # and . in the very end


//solves for some easy empty cells
void empties(grid& nonogram,
                const std::vector<hints>& row_hints,
                const std::vector<hints>& col_hints,
                std::vector<int>& row_boxes_found,
                std::vector<int>& col_boxes_found){
  //rows
  for(unsigned int i=0; i<get_rows(nonogram); i++){
    int tot_boxes=0;  //sum of cells in that row, according to the hints
    for(unsigned int j=0; j<row_hints.at(i).size(); j++){
      tot_boxes+=row_hints.at(i).at(j);
    }
    if(tot_boxes==row_boxes_found.at(i)){   //if all hints of the row had been found, set the rest as empty
      for(unsigned k=0; k<get_cols(nonogram); k++){
        if(nonogram.at(i).at(k)==' '){
          nonogram.at(i).at(k)='x';
        }
      }
    }
  }
  //columns
  for(unsigned int i=0; i<get_cols(nonogram); i++){
    int tot_boxes=0;  //sum of cells in that column, according to the hints
    for(unsigned int j=0; j<col_hints.at(i).size(); j++){
      tot_boxes+=col_hints.at(i).at(j);
    }
    if(tot_boxes==col_boxes_found.at(i)){
      for(unsigned k=0; k<get_rows(nonogram); k++){  //if all hints of the column had been found, empty the rest
        if(nonogram.at(k).at(i)==' '){
          nonogram.at(k).at(i)='x';
        }
      }
    }
  }
}

//solves for some easy filled cells
void boxes(grid& nonogram,
                const std::vector<hints>& row_hints,
                const std::vector<hints>& col_hints,
                std::vector<int>& row_boxes_found,
                std::vector<int>& col_boxes_found){
  //rows
  for(unsigned int i=0; i<get_rows(nonogram); i++){
    if(row_hints.at(i).size()!=0){
      //compare all hints being placed next to each other, starting either from
      //the beginning (forward), or from the end (backwards)
      //if the (correct) hints match on a cell, no matter from which side, 
      //then they are guarenteed to be filled
      std::vector<int> forward (get_cols(nonogram), 0);
      std::vector<int> backward (get_cols(nonogram), 0);
      unsigned int counter=row_hints.at(i).at(0);
      unsigned int hint=1;
      for(unsigned int j=0; j<get_cols(nonogram); j++){   //forward
        if(counter!=0){
          forward.at(j)=1;
          counter--;
        }else{
          forward.at(j)=0;
          if(hint<row_hints.at(i).size()){
          counter = row_hints.at(i).at(hint);
          hint++;
          }
        }
      }
      
      counter=row_hints.at(i).at(0);
      hint=1;
      unsigned int precount=0;
      for(unsigned int z=0; z<row_hints.at(i).size(); z++){
        precount+=row_hints.at(i).at(z);
        precount++;
      }
      precount--;
      precount=get_cols(nonogram)-precount;
      for(unsigned int j=0; j<get_cols(nonogram); j++){   //backward    
        if(precount!=0){
          precount--;
          backward.at(j)=0;
          continue;
        }
        if(counter!=0){
          backward.at(j)=1;
          counter--;
        }else{
          backward.at(j)=0;
          if(hint<row_hints.at(i).size()){
          counter = row_hints.at(i).at(hint);
          hint++;
          }
        }
      }
      unsigned int block_f=1;   //checks so that not just the cells, but also the right hints overlap
      unsigned int block_b=1;   //f. e. if hint nr 2 forwards happens to overlap with hint nr 3 backwards, that's wrong
      for(unsigned int j=0; j<get_cols(nonogram); j++){
        if(forward.at(j)==0&&j!=0){
          if(forward.at(j-1)==1){
            block_f++;
          }
        }
        if(backward.at(j)==0&&j!=0){
          if(backward.at(j-1)==1){
            block_b++;
          }
        }
        if(forward.at(j)==1&&backward.at(j)==1&&block_f==block_b){
          if(nonogram.at(i).at(j)==' '){
          nonogram.at(i).at(j)='!';
          row_boxes_found.at(i)+=1;
          col_boxes_found.at(j)+=1;
          }
        }
      }
    }
  }
  //compare all hints being placed next to each other, starting either from
  //the beginning (forward), or from the end (backwards)
  //if the (correct) hints match on a cell, no matter from which side, 
  //then they are guarenteed to be filled
  for(unsigned int i=0; i<get_cols(nonogram); i++){
    if(col_hints.at(i).size()!=0){
      std::vector<int> forward (get_rows(nonogram), 0);
      std::vector<int> backward (get_rows(nonogram), 0);
      unsigned int counter=col_hints.at(i).at(0);
      unsigned int hint=1;
      for(unsigned int j=0; j<get_rows(nonogram); j++){ //forward
        if(counter!=0){
          forward.at(j)=1;
          counter--;
        }else{
          forward.at(j)=0;
          if(hint<col_hints.at(i).size()){
          counter = col_hints.at(i).at(hint);
          hint++;
          }
        }
      }
      
      counter=col_hints.at(i).at(0);
      hint=1;
      unsigned int precount=0;
      for(unsigned int z=0; z<col_hints.at(i).size(); z++){
        precount+=col_hints.at(i).at(z);
        precount++;
      }
      precount--;
      precount=get_rows(nonogram)-precount;
      for(unsigned int j=0; j<get_rows(nonogram); j++){   //backward  
        if(precount!=0){
          precount--;
          backward.at(j)=0;
          continue;
        }
        if(counter!=0){
          backward.at(j)=1;
          counter--;
        }else{
          backward.at(j)=0;
          if(hint<col_hints.at(i).size()){
          counter = col_hints.at(i).at(hint);
          hint++;
          }
        }
      }
      unsigned int block_f=1;   //checks so that not just the cells, but also the right hints overlap
      unsigned int block_b=1;   //f. e. if hint nr 2 forwards happens to overlap with hint nr 3 backwards, that's wrong
      for(unsigned int j=0; j<get_rows(nonogram); j++){
        if(forward.at(j)==0&&j!=0){
          if(forward.at(j-1)==1){
            block_f++;
          }
        }
        if(backward.at(j)==0&&j!=0){
          if(backward.at(j-1)==1){
            block_b++;
          }
        }
        if(forward.at(j)==1&&backward.at(j)==1&&block_f==block_b){
          if(nonogram.at(j).at(i)==' '){
          nonogram.at(j).at(i)='!';
          col_boxes_found.at(i)+=1;
          row_boxes_found.at(j)+=1;
          }
        }
      }
    }
  }
}

//collects all the fast solving functions
void solve_fast(grid& nonogram,
                const std::vector<hints>& row_hints,
                const std::vector<hints>& col_hints){
  
  std::vector<int> row_boxes_found;
  std::vector<int> col_boxes_found;
  for(unsigned int i=0; i<get_rows(nonogram); i++){
    row_boxes_found.push_back(0);
  }
  for(unsigned int i=0; i<get_cols(nonogram); i++){
    col_boxes_found.push_back(0);
  }

  boxes(nonogram, row_hints, col_hints, row_boxes_found, col_boxes_found);
  empties(nonogram, row_hints, col_hints, row_boxes_found, col_boxes_found);
}


bool check_row(const grid& nonogram,
               const std::vector<hints>& row_hints,
               unsigned int row){
  
  unsigned int sequence=0;      //length of current sequence
  unsigned int hintnr=0;        //nr of current hint per row/col
  bool starter=0;               //true when sequence is ongoing
  
  for(unsigned int col=0; col<get_cols(nonogram); col++){
    if(nonogram.at(row).at(col)=='#'||nonogram.at(row).at(col)=='!'){  
      sequence++;             //increase an ongoing sequence
      starter=1;
    }else if(starter) {
      //if there are hints left, then check their value
      if(row_hints.at(row).size()>hintnr){  
        if(!(sequence==row_hints.at(row).at(hintnr))){
          return false;
        }
      }else{
        return false;
      }
      hintnr++;   //increase the number of used hints by one
      sequence=0; //reset sequence
      starter=0;
    }
  }
  //if the last field was a #, the sequence is has not been finished yet
  if(nonogram.at(row).at(get_cols(nonogram)-1)=='#'||nonogram.at(row).at(get_cols(nonogram)-1)=='!'){
    if (row_hints.at(row).size()>hintnr){ 
      if(!(sequence==row_hints.at(row).at(hintnr))){
        return false;
      }
    }else{
      return false;
    }
    hintnr++;
    sequence=0;
    starter=0;
  }
  //make sure, that every hint had been seen
  if(!(row_hints.at(row).size()==hintnr)){
    return false;
  }
  //reset everything for the next row
  hintnr=0; 
  sequence=0;
  starter=0;
  
 return true;
}


// Check if the filled grid matches the hints.
bool check_solution(const grid& nonogram,
                    const std::vector<hints>& row_hints,
                    const std::vector<hints>& col_hints,
                    bool& solved) {
  unsigned int sequence=0;      //length of current sequence
  unsigned int hintnr=0;        //nr of current hint per row/col
  bool starter=0;               //true when sequence is ongoing
  
  //check all row-hints
  for(unsigned int row=0; row<get_rows(nonogram); row++){
    for(unsigned int col=0; col<get_cols(nonogram); col++){
      if(nonogram.at(row).at(col)=='#'||nonogram.at(row).at(col)=='!'){  
        sequence++;             //increase an ongoing sequence
        starter=1;
      }else if(starter) {
        //if there are hints left, then check their value
        if(row_hints.at(row).size()>hintnr){  
          if(!(sequence==row_hints.at(row).at(hintnr))){
            return false;
          }
        }else{
          return false;
        }
        hintnr++;   //increase the number of used hints by one
        sequence=0; //reset sequence
        starter=0;
      }
    }
    //if the last field was a #, the sequence is has not been finished yet
    if(nonogram.at(row).at(get_cols(nonogram)-1)=='#'||nonogram.at(row).at(get_cols(nonogram)-1)=='!'){
      if (row_hints.at(row).size()>hintnr){ 
        if(!(sequence==row_hints.at(row).at(hintnr))){
          return false;
        }
      }else{
        return false;
      }
      hintnr++;
      sequence=0;
      starter=0;
    }
    //make sure, that every hint had been seen
    if(!(row_hints.at(row).size()==hintnr)){
      return false;
    }
    //reset everything for the next row
    hintnr=0; 
    sequence=0;
    starter=0;
  }
  
  //check all column-hints
  for(unsigned int col=0; col<get_cols(nonogram); col++){
    for(unsigned int row=0; row<get_rows(nonogram); row++){
      if(nonogram.at(row).at(col)=='#'||nonogram.at(row).at(col)=='!'){
        sequence++;             //increase an ongoing sequence
        starter=1;
      }else if(starter){
        //if there are hints left, then check their value
        if(col_hints.at(col).size()>hintnr){
          if(!(sequence==col_hints.at(col).at(hintnr))){
            return false;
          }
        }else{
          return false;
        }
        hintnr++;   //increase the number of used hints by one
        sequence=0; //reset sequence
        starter=0;
      }
    }
    //if the last field was a #, the sequence is has not been finished yet
    if(nonogram.at(get_rows(nonogram)-1).at(col)=='#'||nonogram.at(get_rows(nonogram)-1).at(col)=='!'){
      if(col_hints.at(col).size()>hintnr){
        if(!(sequence==col_hints.at(col).at(hintnr))){
          return false;
        }
      }else{
        return false;
      }
      hintnr++;
      sequence=0;
      starter=0;
    }
    //make sure, that every hint had been seen
    if(!(col_hints.at(col).size()==hintnr)){
      return false;
    }
    //reset everything for the next row
    hintnr=0;
    sequence=0;
    starter=0;
  }
  solved = true;
  return solved;
}

// Solve recursively, filling the grid row-by-row.
bool solve_from(grid& nonogram,
                const std::vector<hints>& row_hints,
                const std::vector<hints>& col_hints,
                unsigned int row, unsigned int col,
                bool& solved,     bool&check_once,     
                unsigned int& sum_marked, unsigned int sum_hints) {

  if(check_once){
    solve_fast(nonogram, row_hints, col_hints);
    check_once=false;
  }

  //std::cout << '\n';
  //print_grid(nonogram);

  if(sum_marked<sum_hints){ //if fillable cells are left, set the current cell as filled
    if(nonogram.at(row).at(col) == ' '){
      nonogram.at(row).at(col) = '#'; 
      sum_marked++;
    }
    if(col<get_cols(nonogram)-1){  //repeat recursively for each column...
      solve_from(nonogram, row_hints, col_hints, row, col+1, solved, check_once, sum_marked, sum_hints);
    }
    else if(row<get_rows(nonogram)-1){ //...and every row
      if(check_row(nonogram, row_hints, row)){
        solve_from(nonogram, row_hints, col_hints, row+1, 0, solved, check_once, sum_marked, sum_hints);
      }
    }
  }else{    //if no more fillable cells are left, set the current cell as empty
    if(nonogram.at(row).at(col) == ' '){  
      nonogram.at(row).at(col) = '.';
    }
  }
  
  //acutal solver
  if(!solved){              //while the solution was not found yet
    if(!(check_solution(nonogram,row_hints, col_hints, solved))){ 
      if(nonogram.at(row).at(col) == '#'){  //if # doesn't work, try .
        unsigned int r=row; 
        unsigned int c=col;
        //empty all fields after the current one, so they can be re-checked again
        while(r<get_rows(nonogram)){
          while(c<get_cols(nonogram)){
            if(nonogram.at(r).at(c) == '#'){
              sum_marked--;
            }
            if(nonogram.at(r).at(c) == '#'||nonogram.at(r).at(c) == '.'){
              nonogram.at(r).at(c) = ' ';
            }
            c++;
          }
          c=0;
          r++;
        }
      nonogram.at(row).at(col) = '.';
      solve_from(nonogram, row_hints, col_hints, row, col, solved, check_once, sum_marked, sum_hints);
      }
    }
  }
  
  //if no solution was found, the mistake happened earlier, so return false and
  //the proccess can be repeated. If a solution was found, the true statement
  //will chain through the recursive functions
  return solved;              
}

// Solve the nonogram, given the grid and the lists of hints.
// Run recursive solver from position (0, 0).
bool solve(grid& nonogram,
           const std::vector<hints>& row_hints,
           const std::vector<hints>& col_hints) {
    unsigned int sum_marked=0;  //sum of all marked cells shall not overcome...
    unsigned int sum_hints=0;   //the sum of of fillable cells according to the hints
    for (unsigned int i = 0; i < row_hints.size(); ++i) {
      for (unsigned int j = 0; j < row_hints.at(i).size(); ++j) {
        sum_hints += row_hints.at(i).at(j);
      }
    }
    bool check_once=logic_test();
    
    bool solved = false;
    solved=solve_from(nonogram, row_hints, col_hints, 0, 0, solved, check_once, sum_marked, sum_hints);
    
    for(unsigned int i=0; i<get_rows(nonogram); i++){
      for(unsigned int j=0; j<get_cols(nonogram); j++){
        if(nonogram.at(i).at(j)=='!'){
          nonogram.at(i).at(j)='#';
        }
        if(nonogram.at(i).at(j)=='x'||nonogram.at(i).at(j)==' '){
          nonogram.at(i).at(j)='.';
        }
      }
    }
    
    return solved;
}

int main() {
  
  grid nonogram;

  std::vector<hints> row_hints, col_hints;

//all the inputs, starting with row, col, 'n'; then all the hints
  read_grid(nonogram, row_hints, col_hints);

  if (!hints_match(row_hints, col_hints)) {
      std::cout << "The numbers in hints do not match!\n";
      return -1;
  }
  
  for(unsigned int i=0; i<row_hints.size(); i++){
    for(unsigned int j=0; j<row_hints.at(i).size(); j++){
      if(row_hints.at(i).at(j)==0){
        row_hints.at(i).erase(row_hints.at(i).begin());
      }
    }
  }
  for(unsigned int i=0; i<col_hints.size(); i++){
    for(unsigned int j=0; j<col_hints.at(i).size(); j++){
      if(col_hints.at(i).at(j)==0){
         col_hints.at(i).erase(col_hints.at(i).begin());
      }
    }
  }
  
  bool solved = solve(nonogram, row_hints, col_hints);
  
  if (solved) {
      std::cout << "FINAL RESULT\n";
      print_grid(nonogram);
  } else {
    std::cout << "No solution found.\n";
  }

  return 0;
}