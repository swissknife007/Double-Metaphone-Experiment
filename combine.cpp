#include <bits/stdc++.h>

using namespace std;

const int MAX = 354984;
map<string,vector<string> > dmap;
map<string,int> fmap;
void init_map()
{
   ifstream f1("dict.txt");
   ifstream f2("dict1");
   
   ofstream f3("inverse_map");

   int iter = 0;
   
   while(iter < MAX)
   {
      string s,t,u;
      getline(f1,s);
      getline(f2,t);
      getline(f2,u);
      s = s.substr(0,s.length()-1);
      t = t.substr(0,t.length()-1);
      u = u.substr(0,u.length()-1);
      
      f3<<s<<" : "<<t<<" "<<u<<endl;
      ::dmap[u].push_back(s);
      ::dmap[t].push_back(s);
      iter++;
   }
   f1.close();
   f2.close();
   f3.close();
   
}
string exec(const char* cmd) 
{
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) 
    {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

string getText(string filename)
{
   ifstream f4(filename.c_str());
   string line;
   string text;
   while(getline(f4,line))
   {
       f4 >> line;
       text += line;
   }
   return text;
}
int LevenshteinDistance(string s, string t)
{
    // degenerate cases
    if (s == t) return 0;
    if (s.length() == 0) return t.length();
    if (t.length() == 0) return s.length();
 
    // create two work vectors of integer distances
    int* v0 = new int[t.length() + 1];
    int* v1 = new int[t.length() + 1];
 
    // initialize v0 (the previous row of distances)
    // this row is A[0][i]: edit distance for an empty s
    // the distance is just the number of characters to delete from t
    for (int i = 0; i < t.length()+1; i++)
        v0[i] = i;
 
    for (int i = 0; i < s.length(); i++)
    {
        // calculate v1 (current row distances) from the previous row v0
 
        // first element of v1 is A[i+1][0]
        //   edit distance is delete (i+1) chars from s to match empty t
        v1[0] = i + 1;
 
        // use formula to fill in the rest of the row
        for (int j = 0; j < t.length(); j++)
        {
            int cost = (s[i] == t[j]) ? 0 : 1;
            v1[j + 1] = min(v1[j] + 1,min( v0[j + 1] + 1, v0[j] + cost));
        }
 
        // copy v1 (current row) to v0 (previous row) for next iteration
        for (int j = 0; j < t.length()+1; j++)
            v0[j] = v1[j];
    }
 
    return v1[t.length()];
}
string processCandidates(string a, vector<string> b)
{
   if(b.size()==0)
   {
      return a;    
   }
   int min_dis = a.length();
   string min_str = a;
   for(int i=0;i<(int)b.size();i++)
   {
       int dis = LevenshteinDistance(a,b[i]);
      // cout<<b[i]<<" ";
       
       if(dis < min_dis  )
       {
          min_dis = dis;
          min_str = b[i];
       }
       else if( dis == min_dis)
       {
           int cf = INT_MAX;
           if(fmap.count(min_str)) cf = fmap[min_str];
           if(fmap.count(b[i]) && cf > fmap[b[i]])
           {
                //cout<< b[i]<<" "<<fmap[b[i]]<<endl;
                min_str = b[i];  
           }
       }
       
   }
   return min_str;
  
}
void read_freq()
{
   ifstream f1("dict3.txt");
   string line;
   int i=0;
   while(getline(f1,line))
   {
     f1>>line;
   
     fmap[line] = ++i;
   }
   f1.close();
}
void processText(string myText)
{
   istringstream iss(myText);
   string token;
   vector<string> metaphones;
   while(getline(iss, token, ' '))
   {
       if(token.length())
       {
         string cmd = "python getcode.py " + token;
         string code = exec(cmd.c_str());
         
         string one = "";code.substr(0,code.find(":"));
         string two = "";code.substr(code.find(":")+1);
         if(code.length()>1) 
         if(code==":") one ="",two="";         
  	//cout <<token<<" "<< code << endl;
         //cout << dmap[one].size() << endl;
         vector<string> candidates;
         for(int i=0;i<(int)dmap[one].size();i++)
         { 
             //cout<<dmap[one][i]<<endl;
             candidates.push_back(dmap[one][i]);
         }
         
         for(int i=0;i<(int)dmap[two].size();i++)
         { 
             //cout<<dmap[two][i]<<endl;
             candidates.push_back(dmap[two][i]);
         }
         string meta = processCandidates(token,candidates);
         cout<<meta<<" "<<endl; 
            
       }
            
   }
   
}

int main()
{
   init_map();
   read_freq(); 
   string myText = getText("twitter_text.in");
   processText(myText);
     
      
   return 0;
}
