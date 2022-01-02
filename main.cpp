#include <iostream>
#include <vector>
#include<set>
#include<map>
#include <string>
#include <queue>
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
 //   printVector(buffer);

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
        //cout<<""<<endl;
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

int main() {
//    vector<int>pa{7,3,1,9,5,3};
//    cout<<getLru(pa,4,3)<<endl;
//  //  cout<<*set.begin()<<endl;
    readInputs();
    printHeader();

    if(algo=="FIFO")fifo();
    else if(algo=="LRU")lru();
    printNumberOfFaults();
    return 0;
}
