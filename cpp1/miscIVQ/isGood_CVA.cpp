//untested
bool isGood(unsigned int k){
  while(1){
    if (k%3 == 0){
      k = k/3;
      continue;
    }// now no more 3's in k
    if (k%5 == 0){
      k = k/5;
      continue;
    }
    if (k%7 == 0){
      k = k/7;
      continue;
    }
    return k == 1;
  }
}
/*return true if k has no other factors beside 3,5 or 7*/
