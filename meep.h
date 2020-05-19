#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
template<class key, class value, class cmp=std::greater<value>>
class Meep
{
private:
    std::unordered_map<key, std::size_t> umap;
    std::vector<std::pair<key,value>> vec;
    std::size_t n=0;
    cmp compare = cmp();
public:
    Meep();
    Meep(std::size_t);
    
    std::size_t insert(key,value);
    auto pop();
    
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

template<class key, class value,class cmp> Meep<key,value,cmp>::Meep() : vec(64) {}
template<class key, class value,class cmp> Meep<key,value,cmp>::Meep(std::size_t i) : vec(i+1) {}

template<class key, class value,class cmp>
std::size_t Meep<key,value,cmp>::fixUp(key k)
{
    std::size_t i = umap[k];
    while(i>1 && compare(vec[i/2].second,vec[i].second)) // compare_repair
    {
        std::swap(vec[i/2],vec[i]);
        std::swap(umap[vec[i/2].first],umap[vec[i].first]);
        i=i/2;
    }
    return i;
}

template<class key, class value,class cmp>
std::size_t Meep<key,value,cmp>::fixDown(key k,std::size_t N)
{
    std::size_t i=umap[k];
    while(2*i <= N)
    {
        std::size_t j = 2*i;
        if(j<N && compare(vec[j].second,vec[j+1].second)) j++; // compare_repair
        if(!compare(vec[i].second,vec[j].second)) break; // compare_repair
        std::swap(vec[i],vec[j]);
        std::swap(umap[vec[i].first],umap[vec[j].second]);
        i=j;
    }
    return i;
}
template<class key, class value, class cmp> 
std::size_t Meep<key,value,cmp>::insert(key k, value v)
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

template<class key, class value, class cmp> 
void Meep<key,value,cmp>::display()
{
    for(std::size_t i=1;i<=n;i++)
    {
        std::cout << vec[i].first << " " << vec[i].second << " " << umap[vec[i].first] << std::endl;
    }
}

template<class key, class value, class cmp>
auto Meep<key,value,cmp>::pop()
{
    std::swap(umap[vec[1].first],umap[vec[n].first]);
    std::swap(vec[1],vec[n]);
    umap[vec[n].first]=0;
    fixDown(umap[vec[1].first],n-1);
    return vec[n--];
}
template<class key, class value, class cmp>
std::size_t Meep<key,value,cmp>::change(key k, value v)
{
    std::size_t i=umap[k];
    bool compare_result = compare(vec[i].second,v);
    vec[i].second=v;
    if(compare_result==true) // which means the current value is larger than v
        return fixUp(k); // then we need to get the key k with the new value v up the heap
    else
        return fixDown(k); // if it's the other way around ( less than or equal to )
        // we can eliminate the equal to, because fixDown in this case will make the heap untouched
}
template<class key, class value,class cmp>
std::size_t Meep<key,value,cmp>::searchIndex(key k)
{
    return umap[k];
}

template<class key, class value, class cmp>
value Meep<key,value,cmp>::searchValue(key k)
{
    return vec[umap[k]].second;
}