#include <iostream>
#include <sys/time.h> //timeval
using namespace std;

int main(){
    struct timeval tval;
    gettimeofday (&tval,NULL); //populates the struct
    
    struct tm * ptm = gmtime( &tval.tv_sec ); //pass in current or any epoch number
    
    cout<<ptm->tm_year +1900 <<endl;
    cout<<ptm->tm_mon+1 <<endl;
    cout<<ptm->tm_mday <<endl;
    cout<<ptm->tm_hour <<endl;
    cout<<ptm->tm_min <<endl;
    cout<<ptm->tm_sec <<endl;
    cout<<tval.tv_usec<<endl;
}/* Req: break up any epoch number into year/month/../sec

If given current time, then also print microsec offset
*/
