#include <iostream>
#include <vector>
#include<set>
#include<map>
#include <string>
#include <queue>
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
    printNumberOfFaults();
}
int main() {
    readInputs();
    printHeader();
    if(algo=="FIFO")fifo();
    return 0;
}
