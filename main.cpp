#include <iostream>
#include <vector>
#include<set>
#include<map>
#include <string>
#include <queue>
#include <algorithm>
#include<unordered_set>
using namespace std;

vector<int>buffer;
int nPages=0;
string algo="";
int numOfPageFaults=0;

void printVector(const vector<int>vector){
    for(auto i:vector){
        cout<<i<<endl;
    }
}
string twoDigits(int val){
    string twoNums="";
    if(val<10){
        twoNums=to_string(val);
        twoNums="0"+twoNums;
        return twoNums;
    }
    return to_string(val);

}
void printVectorInline(int page,const vector<int>vector,string status=" "){
    cout<<twoDigits(page)<<" "<<status<<"    ";
    for(auto i:vector){
        cout<<twoDigits(i)<<" ";
    }
}
void printNumberOfFaults(){
    cout<<"-------------------------------------"<<endl;
    cout<<"Number of page faults = "<<numOfPageFaults<<endl;
}
void printHeader(){
    cout<<"Replacement Policy = "<<algo<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"Page   Content of Frames"<<endl;
    cout<<"----   -----------------"<<endl;
}
void readInputs(){
    cin>>nPages;
    cin>>algo;
    int n=0;
    cin>>n;
    while(n!=-1){
        buffer.push_back(n);
        cin>>n;
    }

}
vector<int> findOptimal(int l,vector<int>contentOfFrame,vector<int>buf,int numPages){
    vector<int>optimalVector;
    for(int i=l;i<buf.size();i++){
        if(optimalVector.size()!=numPages){
            // make sure that the optimal exists in the contentOfFrame
            if(find(contentOfFrame.begin(), contentOfFrame.end(), buf[i])!=contentOfFrame.end()){
                if(find(optimalVector.begin(), optimalVector.end(), buf[i])==optimalVector.end()){
                    optimalVector.push_back(buf[i]);
                }
            }
        }
    }
    return optimalVector;
}
vector<int> getDifference(vector<int>contFrame,vector<int>future){
    vector<int>difference;
    for(int i=0;i<contFrame.size();i++){
        int contFrameVal=contFrame[i];
        bool inside=false;
        for(int j=0;j<future.size();j++){
            int futureVal=future[j];
            if(futureVal==contFrameVal){
                inside=true;
                break;
            }
        }
        if(!inside)difference.push_back(contFrameVal);
    }
    return difference;
}
void optimal(){
    vector<int>contentOfFrame;
    queue<int>queue;
    string status="";
    for(int i=0;i<buffer.size();i++){
        int page=buffer[i];
        if(find(contentOfFrame.begin(), contentOfFrame.end(), page)==contentOfFrame.end()){
            // find optimal that will be replaced
            if(contentOfFrame.size()==nPages){
                vector<int>optVec= findOptimal(i+1,contentOfFrame,buffer,nPages);
                int optVal;
                if(optVec.size()!=nPages){
                    optVal= getDifference(contentOfFrame,optVec)[0];
                }
                else
                 optVal=optVec[optVec.size()-1];
                // get index of the optimal in contentOfFrame
               int optIndexInFrame=find(contentOfFrame.begin(), contentOfFrame.end(), optVal)-contentOfFrame.begin();
               contentOfFrame[optIndexInFrame]=page;
               status="F";
               numOfPageFaults++;
            }
            else{
                contentOfFrame.push_back(page);
                status=" ";
            }
        }
        else status=" ";
        printVectorInline(page,contentOfFrame,status);
        cout<<""<<endl;
    }
}
void fifo(){
    // intialize queue
    queue<int>queue;
    vector<int>contentOfFrame;
    string status="";
    for(int i=0;i<buffer.size();i++){
        int page=buffer[i];
        if(std::find(contentOfFrame.begin(), contentOfFrame.end(), page)==contentOfFrame.end()) {
            if (queue.size() == nPages) {
                int front = queue.front();
                queue.pop();
                // find index of the front page in the queue
                auto frontIndex =
                        std::find(contentOfFrame.begin(), contentOfFrame.end(), front) - contentOfFrame.begin();
                contentOfFrame[frontIndex] = page;
                // update the queue
                queue.push(page);
                numOfPageFaults++;
                status="F";
            } else {
                queue.push(page);
                contentOfFrame.push_back(page);
                status=" ";
            }

        }
        else status=" ";
        printVectorInline(page,contentOfFrame,status);
        cout<<""<<endl;
    }

}
int getLru(vector<int>page,int index,int size){
    int lruVal=0;
    set<int>set;
    for(int i=index-1;i>=0;i--){
        if(set.size()==size){
            break;
        }
        else {
            lruVal = page[i];
            set.insert(page[i]);
        }
    }
    return lruVal;
}
void lru(){
    vector<int>contentOfFrame;
    string status="";
    for(int i=0;i<buffer.size();i++){
        int page=buffer[i];
        if(std::find(contentOfFrame.begin(), contentOfFrame.end(), page)==contentOfFrame.end()) {
            if (contentOfFrame.size() == nPages) {
                // first element in vector will be the least recently used
                int leastUsed = getLru(buffer,i,nPages);
                status = "F";
                numOfPageFaults++;
                int lUIndexInContent =
                        find(contentOfFrame.begin(), contentOfFrame.end(), leastUsed) - contentOfFrame.begin();
                contentOfFrame[lUIndexInContent] = page;
            } else {
                contentOfFrame.push_back(page);
                 status=" ";
            }
        }
        else status=" ";
        printVectorInline(page,contentOfFrame,status);
        cout<<""<<endl;

    }
}
int findUnused(int pointer,vector<int>&bits){
   while(bits[pointer%nPages]!=0){
       bits[pointer%nPages]=0;
       pointer=(pointer%nPages)+1;
   }
    return pointer;
}
void clockReplacement(){
    vector<int>contentOfFrame;
    vector<int>bits;
    int pointer=0;
    string status="";
    for(int i=0;i<buffer.size();i++){
        int page=buffer[i];
        if(std::find(contentOfFrame.begin(), contentOfFrame.end(), page)==contentOfFrame.end()){
            if(contentOfFrame.size()==nPages){
                pointer= findUnused(pointer,bits);
                contentOfFrame[pointer%nPages]=page;
                bits[pointer%nPages]=1;
                pointer++;
                status="F";
                numOfPageFaults++;
            }
            else{
                contentOfFrame.push_back(page);
                bits.push_back(1);
                pointer++;
                status=" ";
            }
        }

        else {
           int hitIndex=find(contentOfFrame.begin(), contentOfFrame.end(), page)-contentOfFrame.begin();
            bits[hitIndex]=1;
            status = " ";
        }
        printVectorInline(page,contentOfFrame,status);
        cout<<""<<endl;
    }
}

int main() {
    readInputs();
    printHeader();
    if(algo=="FIFO")fifo();
    else if(algo=="LRU")lru();
    else if(algo=="OPTIMAL")optimal();
    else if(algo=="CLOCK")clockReplacement();
    printNumberOfFaults();
    return 0;
}
