#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    enum ING
    {
        UNKNOWN = 0,
        SUP_MIN_HASH = 1,
        REC_MIN_HASH = 1000
    };
    std::vector<int> topo_sort_bfs(const int &n, const std::map<int, std::vector<int>> &adj)
    {
        std::unordered_map<int, int> in_degree;
        std::vector<int> result;
        std::queue<int> q;

        for (const auto &[node, neighbors] : adj)
        {
            if (in_degree.find(node) == in_degree.end())
            {
                in_degree[node] = 0;
            }
            for (int neighbor : neighbors)
            {
                in_degree[neighbor]++;
            }
        }

        for (const auto &[node, deg] : in_degree)
        {
            if (deg == 0)
            {
                q.push(node);
            }
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            result.push_back(u);
            if(adj.count(u)==0){
                continue;
            }
            for (int v : adj.at(u))
            {
                if (--in_degree[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        if (result.size() != in_degree.size())
        {
            return {};
        }

        return result;
    }
    vector<string> findAllRecipes(vector<string> &recipes, vector<vector<string>> &ingredients, vector<string> &supplies)
    {
        std::map<std::string, int> hash_map;
        std::map<int, bool> valid_sups;
        std::vector<std::string> valid_recipes;
        int sup_int = SUP_MIN_HASH; // supplies 1 - 999
        int sup_rec = REC_MIN_HASH; // recipes 1000 - 9999
        int n = recipes.size();
        auto mark_as_valid = [&](const int &rec)
        {
            int rec_idx = rec - ING::REC_MIN_HASH;
            if (!valid_sups[rec]){
                valid_recipes.emplace_back(recipes[rec_idx]);
            }
            valid_sups[rec] = true;
        };
        for (const auto &sup : supplies)
        {
            valid_sups[sup_int] = true;
            hash_map[sup] = sup_int++;
        }
        for (const auto &rec : recipes)
        {
            hash_map[rec] = sup_rec++;
        }
        std::map<int, std::vector<int>> adj;
        for (int i = 0; i < n; ++i)
        {
            auto &rec_hash = hash_map[recipes[i]];
            for (const auto &ing : ingredients[i])
            {
                auto &ing_hash = hash_map[ing];
                if (ing_hash >= ING::REC_MIN_HASH && ing_hash != ING::UNKNOWN)
                {
                    adj[rec_hash].emplace_back(ing_hash);
                }
            }
            if(adj.count(rec_hash) == 0){
                mark_as_valid(rec_hash);
            }
            
        }
        std::vector<int> topo_ord_recipes = topo_sort_bfs(n, adj);
        for (const int &rec : topo_ord_recipes)
        {
            if (adj[rec].empty())
            {
                mark_as_valid(rec);
                continue;
            }
            bool flag = true;
            for (const int &ing : adj[rec])
            {
                if (!valid_sups[ing])
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                mark_as_valid(rec);
            }
        }
        return valid_recipes;
    }
};
int main(){

    Solution s;
    vector<string> r = {"bread","sandwich","burger"};
    vector<vector<string>> i = {{"yeast","flour"},{"bread","meat"}
                ,{"sandwich","meat","bread"}};
    vector<string> S = {"yeast","flour","meat"};
    
    s.findAllRecipes(r,i,S);


}
