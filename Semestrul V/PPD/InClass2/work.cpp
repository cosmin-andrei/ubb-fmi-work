////
//// Created by Cosmin on 10/14/2024.
////
//
//#include <iostream>
//#include <thread>
//#include <functional>
//#include <vector>
//
//#define length 100
//
//using namespace std;
//
//void init_vector(int a[]) {
//    for (int i = 0; i < length; i++)
//        a[i] = i;
//
//}
//
//void calculeazaSuma(int a[], int b[], int c[]) {
//    for (int i = 0; i < length; i++)
//        c[i] = a[i] + b[i];
//}
//
//int main() {
//
//    int a[length], b[length], c[length];
//    auto t_start = chrono::steady_clock::now();
//    init_vector(a);
//    calculeazaSuma(a, b, c);
//    auto t_final = chrono::steady_clock::now();
//    auto diff= t_final - t_start;
//    cout<<"Time: "<<chrono::duration <double, milli> (diff).count()<<" ms"<<endl;
//}

//#include <iostream>
//#include <thread>
//#include <functional>
//
//using namespace std;
//
//void f0(int a) {
//    auto id = this_thread::get_id();
//    uint64_t p_id = (uint64_t) &id;
//    cout<< "I am thread no."<<a<<"ID: "<<p_id<<endl;
//
//    if (a < 10) {
//        thread t(f0, a + 1);
//        t.join();
//    }
//}
//
//void f1(int a, int &b, std::function<int(int, int)> f) {
//    auto id = this_thread::get_id();
//    uint64_t p_id = (uint64_t) &id;
//    cout << "Thread id: " << p_id << endl;
//}
//
//int test0() {
//    auto t_start = chrono::steady_clock::now();
//    thread t1(f0, 1);
//
//    auto id1 = t1.get_id();
//    int x = 2, y = 3;
//
//    thread t2(f1, x, std::ref(y), [=](int xx, int yy) { return xx + yy; });
//    auto id2 = t2.get_id();
//
//    cout << "Thread 1 id: " << id1 << endl;
//    this_thread::sleep_for(std::chrono::seconds(3));
//    cout << "Thread 2 id: " << id2 << endl;
//
//    t1.join();
//    t2.join();
//
//    auto t_end = chrono::steady_clock::now();
//}
//
//int main() {
//
//    if(test0_mutex()==0)
//        cout<<"Test 0 passed"<<endl;
//    else
//        cout<<"Test 0 failed"<<endl;
//
//    return 0;
//}
