#include <iostream>
#include <unordered_map>
#include <vector>
template<class key, class value>
class Meep
{
private:
    std::unordered_map<key, std::size_t> umap;
    std::vector<std::pair<key,value>> vec;
    std::size_t n=0;
public:
    Meep();
    Meep(std::size_t);
    
    std::size_t insert(key,value);
    auto getMin();
    
    std::size_t size();
    int empty() { return n==0; }
    int full() { return n==vec.size()-1;}
    std::size_t fixUp(key k);
    std::size_t fixDown(key k, std::size_t N);
    value searchValue(key);
    std::size_t searchIndex(key);
    void display();
    std::size_t change(key, value);
    
    bool has(key k)
    {
        return umap[k]!=0;
    }
};
//template<class key, class value> Meep<key,value>::

template<class key, class value> Meep<key,value>::Meep() : vec(64) {}
template<class key, class value> Meep<key,value>::Meep(std::size_t i) : vec(i+1) {}

template<class key, class value>
std::size_t Meep<key,value>::fixUp(key k)
{
    std::size_t i = umap[k];
    while(i>1 && vec[i/2].second > vec[i].second)
    {
        std::swap(vec[i/2],vec[i]);
        std::swap(umap[vec[i/2].first],umap[vec[i].first]);
        i=i/2;
    }
    return i;
}

template<class key, class value>
std::size_t Meep<key,value>::fixDown(key k,std::size_t N)
{
    std::size_t i=umap[k];
    while(2*i <= N)
    {
        std::size_t j = 2*i;
        if(j<N && vec[j].second > vec[j+1].second) j++;
        if(!(vec[i].second > vec[j].second)) break;
        std::swap(vec[i],vec[j]);
        std::swap(umap[vec[i].first],umap[vec[j].second]);
        i=j;
    }
    return i;
}
template<class key, class value> 
std::size_t Meep<key,value>::insert(key k, value v)
{
    if(!full())
    {
        umap[k]=++n;
        vec[n].first=k;
        vec[n].second=v;
        return fixUp(k);
    }
    return 0;
}

template<class key, class value> 
void Meep<key,value>::display()
{
    for(std::size_t i=1;i<=n;i++)
    {
        std::cout << vec[i].first << " " << vec[i].second << " " << umap[vec[i].first] << std::endl;
    }
}

template<class key, class value>
auto Meep<key,value>::getMin()
{
    std::swap(umap[vec[1].first],umap[vec[n].first]);
    std::swap(vec[1],vec[n]);
    umap[vec[n].first]=0;
    fixDown(umap[vec[1].first],n-1);
    return vec[n--];
}
template<class key, class value>
std::size_t Meep<key,value>::change(key k, value v)
{
    std::size_t i=umap[k];
    vec[i].second=v;
    return fixUp(k);
}
template<class key, class value>
std::size_t Meep<key,value>::searchIndex(key k)
{
    return umap[k];
}

template<class key, class value>
value Meep<key,value>::searchValue(key k)
{
    return vec[umap[k]].second;
}