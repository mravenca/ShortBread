// ShortBreadLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "ShortBreadLibrary.h"

using namespace std;

vector<string> lines;

map <string, vector<string>> dict;
vector<string> cws;

map<string, list<string>> adjListsM;
map<string, string> pred;
map<string, int> dist;

bool GetFileContent(string fileName, int WordLength)
{
    // Open the File
    ifstream in(fileName.c_str());
    // Check if object is valid
    if (!in)
    {
        cerr << "Cannot open the File : " << fileName << endl;
        return false;
    }
    string str;
    // Read file lines with specified length 
    while (getline(in, str))
    {
        for (int i = 0; i < str.length(); i++)
            str[i] = tolower(str[i]);
        //If line contains string of a specified length then save it in vector
        if ((str.size() > 0) && (str.length() == WordLength))
        {
            lines.push_back(str);
        }

    }
    // Close file
    in.close();
    return true;
}
string genCW2(string word1, int pos)
{

    string res;
    int i;
    string wildcard = ".";

    for (i = 0; i < pos; i++)
    {
        res += word1[i];
    }

    res += wildcard;
    for (i = pos + 1; i < word1.length(); i++)
    {
        res += word1[i];
    }

    return res;
}
void add_edge(string src, string dest)
{
    adjListsM[src].push_back(dest);
    adjListsM[dest].push_back(src);
}
string findCommonRoot(string word1, string word2)
{
    //find a group of letters, that forms word from a dictionary when we add one letter to it
    string mw1, mw2;
    for (int i = 0; i < word1.length(); i++)
    {
        mw1 = genCW2(word1, i);
        mw2 = genCW2(word2, i);
        if (mw1 == mw2)
            return mw1;
    }
    mw1 = "";
    return mw1;
}
bool buildDict()
{
    string cw;
    string word;
    vector<string>::iterator itr;
    std::cout << "Building dictionary.." << endl;

    for (string lineA : lines)
    {
        for (string lineB : lines)
        {
            if (lineA == lineB)
                break;
            cw = findCommonRoot(lineA, lineB);

            if (cw.length() > 0)
            {
                //update dict
                vector<string>row = dict[cw];
                vector<string>r = row;

                if (!std::count(r.begin(), r.end(), lineB))
                {
                    r.push_back(lineB);
                }

                dict[cw] = r;
                r.clear();

                itr = find(cws.begin(), cws.end(), cw);
                if (itr == cws.end())
                {
                    cws.push_back(cw);
                }


            }
        }
        std::cout << ".";
    }
    return true;
}

bool buildGraph()
{
    //Builds a graph from the words of the word list;
    //Word A is connected to word B if B can be obtained from A by changing one letter
    for (string gr : cws)
    {
        vector<string> words;
        words = dict[gr];

        for (string a : words)
        {
            for (string b : words)
            {
                if (a == b) break;
                add_edge(a, b);
            }

        }
    }


    for (string gr1 : cws)
    {
        for (string gr2 : cws)
        {
            if (gr1 == gr2) break;
            vector<string> words1;
            vector<string> words2;
            words1 = dict[gr1];
            words2 = dict[gr2];

            for (string a : words1)
                for (string b : words2)
                {
                    if (a == b) break;
                    regex pat(gr1);
                    regex pat2(gr2);
                    if (regex_match(a, pat) && regex_match(b, pat))
                    {

                        cout << "a: " << a << " matches pattern " << gr1 << ",b: " << b << " matches pattern " << gr1 << endl;

                        add_edge(a, b);
                    }
                    if (regex_match(a, pat2) && regex_match(b, pat2))
                    {

                        cout << "a: " << a << " matches pattern " << gr2 << ",b: " << b << " matches pattern " << gr2 << endl;

                        add_edge(a, b);
                    }

                }
        }
    }

    return true;
}
bool PrepareGraph()
{
    buildDict();
    buildGraph();
    return true;
}
bool BFS(string src, string dest)
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<string> queue;

    // Map visited which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    map<string, bool> visited; //puvodne bool visited[v];

    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    // standard BFS algorithm
    while (!queue.empty()) {
        string u = queue.front();
        queue.pop_front();
        for (auto i : adjListsM[u]) {
            if (visited[i] == false) {
                visited[i] = true;
                dist[i] = dist[u] + 1;
                pred[i] = u;
                queue.push_back(i);

                // We stop BFS when we find
                // destination.
                if (i == dest)
                    return true;
            }
        }
    }

    return false;
}

bool getShortestDistance(std::string source, std::string dest)
{
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    
    if (BFS(source, dest) == false) {
        std::cout << "Given source and destination are not connected";
        return false;
    }

    // vector path stores the shortest path
    vector<string> path;
    string crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != "") {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    // distance from source is in distance array
    std::cout << "Shortest path length is : " << dist[dest];

    // printing path from source to destination
    std::cout << endl << "Path is:" << endl;
    for (int i = path.size() - 1; i >= 0; i--)
        std::cout << path[i] << " ";

    return true;
}
