#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

class Graph
{
private:
    vector<vector<unsigned> > graph;
    vector<unsigned> result;
    unsigned N;

public:
    Graph()
    {
        N = 0;
    }

    ~Graph()
    {
        N = 0;
    }

    Graph(const  vector<vector<unsigned>>& input)
    {
        for (unsigned int i = 0; i < input.size(); ++i)
        {
            for (const auto& j : input[i])
            {
                if ( j >= input.size())
                    throw length_error("fail");
            }
        }
        graph = input;
        N = graph.size();
    }

    void read(istringstream& stream)
    {
        graph.clear();
        string stroka;
        while (getline(stream, stroka))
        {
            istringstream stream(stroka);
            unsigned n;
            char op;
            if (stream >> n && stream >> op && op == ':')
            {
                N = n + 1;
                int value;
                vector<unsigned> time;
                while (stream >> value)
                {
                    time.push_back(value);
                }
                graph.push_back(time);
            }
        }
    }

    Graph(const Graph& other)
    {
        N = other.N;
        graph = other.graph;
        if (!(other.result.empty()))
            result = other.result;
    }

    Graph operator=(const Graph& other)
    {
        if (this != &other)
        {
            N = other.N;
            graph = other.graph;
            if (!other.result.empty())
                result = other.result;
        }
        return (*this);
    }

    void dfs(unsigned index)
    {
        vector<bool> run_;
        result.clear();
        for (unsigned i = 0; i < N; ++i)
        {
            run_.push_back(false);
        }
        dfs_help(index, run_);
    }

    void dfs_help(unsigned index, vector<bool>& run_)
    {
        run_[index] = true;
        result.push_back(index);
        for (const auto& i : graph[index])
        {
            if (!(run_[i]))
                dfs_help(i, run_);
        }
    }

    void print_result(ostream& stream) const
    {
        for (unsigned i : result)
            stream << "->" << i;
    }

    void print_graph(ostream& stream) const
    {
        for (unsigned i = 0; i < N; i++)
        {
            stream << i << ":";
            for (const auto j : graph[i])
            {
                stream << j << " ";
            }
            stream << endl;
        }
    }
};
