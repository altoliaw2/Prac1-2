#include <iostream>
#include <string>
#include <algorithm>

char** fn_DecArrBasic();
std::pair<char*, int*> fn_DecArrSpec();
void fn_RemDyMem(char** c2p_Arr, int i_Row);
std::string fn_CoutRes(const char& ccref_Alb, const int& ciref_Dir, char** c2p_Basic, char* cp_Spec, int* ip_Spec);

int main(){
    char** c2p_Basic        = nullptr;// COM: general map
    char* cp_Spec           = nullptr;// COM: some special characters
    int* ip_Spec            = nullptr;// COM: the replacement of the index in 2D21D


    //COM: generating the two 2D arrays and one 1D array
    c2p_Basic               = fn_DecArrBasic();
    std::pair<char*, int*> obj_Pair = fn_DecArrSpec();
    cp_Spec                 = obj_Pair.first;
    ip_Spec                 = obj_Pair.second;

    int i_NumRow            = -1;
    std::cin>>  i_NumRow;
    std::string s_Res       = "";
    for(int i_Ct= 0; i_Ct< i_NumRow; i_Ct++){
        char c_Alb          =   '\0';
        int i_Dir           =   -1;
        std::cin>> c_Alb>> i_Dir;
        s_Res               += fn_CoutRes(c_Alb, i_Dir, c2p_Basic, cp_Spec, ip_Spec);
    }
    std::cout<< s_Res;

    fn_RemDyMem(c2p_Basic, 4);
    delete [] cp_Spec;
    delete [] ip_Spec;

    return 0;
}

char** fn_DecArrBasic(){
    char** c2p_Basic    =   new char*[4];
    *(c2p_Basic + 0)    =   new char[10] {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    *(c2p_Basic + 1)    =   new char[10] {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'};
    *(c2p_Basic + 2)    =   new char[10] {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';'};
    *(c2p_Basic + 3)    =   new char[10] {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'};
    return c2p_Basic;
}

std::pair<char*, int*> fn_DecArrSpec(){
    char* cp_Spec       =   new char[14] {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', ':', '<', '>', '?'};
    int* ip_Spec        =   new int[14]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 29, 37, 38, 39};
    return std::pair<char*, int*>(cp_Spec, ip_Spec);
}

std::string fn_CoutRes(const char& ccref_Alb, const int& ciref_Dir, char** c2p_Basic, char* cp_Spec, int* ip_Spec){
    // COM: Checking if the alphabet is in the array
    char* cp_Pos        = std::find(cp_Spec, (cp_Spec + 14), ccref_Alb);
    int i_GenInd        = -1;

    if(cp_Pos != (cp_Spec + 14)){// COM: hitting
        int i_IndSpec       = -1;
        i_IndSpec       = (cp_Pos  - cp_Spec);
        i_GenInd        = ip_Spec[i_IndSpec];
    }
    else{// COM: missing
        for(int i_Ct=0; i_Ct< 4; i_Ct++){
            char* cp_Pos    = std::find(c2p_Basic[i_Ct], (c2p_Basic[i_Ct] + 10), ccref_Alb);
            if(cp_Pos != (c2p_Basic[i_Ct] + 10)){// COM: hitting
                i_GenInd= 10* i_Ct+ (cp_Pos- c2p_Basic[i_Ct]);
                break;
            }
        }
    }
    if(i_GenInd!= -1){// COM: hitting
            switch(ciref_Dir){
                case 1:
                    i_GenInd -=10;
                break;
                case 2:
                    i_GenInd +=10;
                break;
                case 3:
                    i_GenInd +=1;
                break;
                case 4:
                    i_GenInd -=1;
                break;
                default:
                    exit(1);
                break;
            }
            if(i_GenInd < 0){
                i_GenInd = 40 + i_GenInd;
            }

            int i_Row = i_GenInd/ 10;
            int i_Col = i_GenInd% 10;
            std::string s_Tmp(1, c2p_Basic[i_Row][i_Col]);
            return s_Tmp+"\n";
        }
        else{
            std::cerr<< "Error";
            exit(1);
        }

}

void fn_RemDyMem(char** c2p_Arr, int i_Row){
    for(int i_Ct=0; i_Ct < i_Row ; i_Ct++){
        delete [] c2p_Arr[i_Ct];
    }
}
