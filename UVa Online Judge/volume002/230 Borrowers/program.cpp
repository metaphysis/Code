// Borrowers
// UVa ID: 230
// Verdict: Accepted
// Submission Date: 2016-05-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct book
{
    int index;
    bool borrowed;
    string title, author;
    
    bool operator<(book x) const
    {
        if (author != x.author)
            return author < x.author;
        else
            return title < x.title;
    }
};

vector<book> books, returned;

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line) && line != "END")
    {
        int index = line.find('\"', 1);
        string title = line.substr(1, index - 1);
        string author = line.substr(index + 5);

        book aBook;
        aBook.title = title;
        aBook.author = author;
        books.push_back(aBook);
    }
    
    sort(books.begin(), books.end());
    
    map<string, int> indexer;
    for (int i = 0; i < books.size(); i++)
    {
        books[i].index = i;
        books[i].borrowed = false;
        indexer.insert(make_pair(books[i].title, i));
    }
        
    while (getline(cin, line) && line != "END")
    {
        if (line[0] == 'B')
        {
            string title = line.substr(8, line.length() - 9);
            books[indexer[title]].borrowed = true;
        }
        else if (line[0] == 'R')
        {
            string title = line.substr(8, line.length() - 9);
            returned.push_back(books[indexer[title]]);
        }
        else
        {
            sort(returned.begin(), returned.end());
            
            for (int i = 0; i < returned.size(); i++)
            {
                bool found = false;
                for (int j = returned[i].index; j >= 0; j--)
                    if (books[j].borrowed == false)
                    {
                        cout << "Put \"" << returned[i].title << "\" after \"";
                        cout << books[j].title << "\"" << endl;
                        found = true;
                        break;
                    }
                    
                if (found == false)
                    cout << "Put \"" << returned[i].title << "\" first" << endl;

                books[returned[i].index].borrowed = false;
            }
            
            cout << "END" << endl;
            
            returned.clear();
        }
    }
 
	return 0;
}
