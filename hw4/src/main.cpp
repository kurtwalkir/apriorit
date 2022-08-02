#include <simpleThreadPool.h>

void task() {
    cout<<"Task"<<endl;
}

int main(int argc, char** argv)
{
    try {
        SimpleThreadPool pool(3);
        std::vector<std::future<void>> results;

        for (size_t indx = 0; indx < 8; ++indx)
        {
            results.emplace_back(std::move(pool.Post(task)));
        }
    } catch (const exception& e) {
        cout<<e.what()<<endl;
    }
}
