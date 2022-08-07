#include <linkedList.h>

using namespace hw7;

int main(int argc, char const *argv[])
{
    try {
        LinkedList<std::string> list;
        list.push_front("Anton");
        list.push_front("Alex");
        list.push_front("Hanna");

        /* Copy ctr */
        LinkedList<std::string> list2 = list;
        list2.push_front("Maksym");

        for (const auto &it: list) {
            std::cout << it << std::endl;
        }

        for (const auto &it: list2) {
            std::cout << it << std::endl;
        }

        /* Assignment operator */
        LinkedList<std::string> list3;
        list3 = list2;

        for (const auto &it: list3) {
            std::cout << it << std::endl;
        }

        /* Move ctr */
        LinkedList<std::string> list4(std::move(list3));
        for (const auto &it: list4) {
            std::cout << it << std::endl;
        }

        /* Initializer list ctr */
        LinkedList<std::string> list5 = {"Anne", "Michel", "John"};
    } catch(const exception & e) {
        cout<<e.what()<<endl;
    }
    return 0;
}