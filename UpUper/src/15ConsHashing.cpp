//普通哈希算法：同一个客户端，永远会被映射到一个指定的Sever，有效的解决会话共享问题，
//但是当一个服务器挂了或增加，原来%3变成%2，导致原来正常连接的又指向了其他服务器，以及缓存和DB（数据库）之间的问题

//一致性哈希算法：分布式负载均衡的首选算法--后端接入n台服务器，接到请求之后，需要将请求平均发到每台服务器上
//具有良好的单调性，重新哈希也不会导致大量重新映射
//一致性哈希环的虚拟节点：md5算法：真的主机会对于100-200个虚拟节点，防止物理节点过少，导致不分散

#include<iostream>
#include<string>
#include<set> // 红黑树
#include<list>
using namespace std;

// using unit = unsigned int;

// class PhscialHost; //前置申明物理主机类型

// class VirtualHost//虚拟节点
// {
// private:
//     string ip_;
//     int md5_;
//     PhscialHost* PhscialHost_;  //隶属物理节点

// public:
//     VirtualHost(string ip, PhscialHost *p)
//         :ip_(ip)
//         ,PhscialHost_(p)
//         {
//             // md5_ = 
//         }

// };


// class PhscialHost //物理节点
// {
// private:
//     string ip_;
//     list<VirtualHost> VirtualHosts_;  //虚拟节点列表
// public:
//     PhscialHost(string ip,int vnumber)
//         :ip_(ip)
//     {
//         for(int i =0;i<vnumber;i++)
//         {
//             //虚拟节点需要一个ip，也需要记录属于哪个节点
//             // VirtualHosts_.emplace_back(
//             //     ip + "#" + ::to_string(i),
//             //     this
//             // );
//         }
//     }

//     string getIP()  const
//     {
//         return ip_;
//     }

//     const list<VirtualHost>& VirtualHosts_() const
//     {
//         // return VirtualHosts_;
//     }

    
// };

// //一致性哈希
// class ConsistentHash
// {

// };


// int main()
// {

// }