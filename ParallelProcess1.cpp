#include <thread>
#include <iostream>
#include <chrono>
#include <vector>
#include <string>  
#include <algorithm>  
#include <mutex>

using namespace std::chrono;

std::atomic<long long int> primeSum = 2;
std::atomic<int> totalPrimes = 1;
std::vector<int> maxPrimes(10, 0);
std::mutex m;

void isPrime(int n)
{
    std::vector<int> localMaxPrimes;
    int allPrimes = 0;
    long long int sum = 0;
    int maxPrime = 0;
    bool flag;
    for (int p = n; p < 1e+8; p = p + 16) {
        flag = true;
        if (p <= 1)
            continue;
        if (p <= 3) {
            allPrimes++;
            sum += p;
        }

        if (p % 2 == 0 || p % 3 == 0)
            continue;

        for (int i = 5; i * i <= p; i = i + 6)
            if (p % i == 0 || p % (i + 2) == 0) {
                flag = false;
                break;
            }

        if (flag) {
            allPrimes++;
            sum += p;
            if (maxPrime < p) {
                maxPrime = p;
                if (p > 99999000) {
                    localMaxPrimes.push_back(maxPrime);
                }
            }
        }
    }

    totalPrimes += allPrimes;
    primeSum += sum;

    m.lock();
    for (int i = 0; i < localMaxPrimes.size(); i++) {
        maxPrimes.push_back(localMaxPrimes[i]);
    }
    m.unlock();
}


int main()
{
    auto start = high_resolution_clock::now();
    std::thread worker1(isPrime, 3);
    std::thread worker2(isPrime, 5);
    std::thread worker3(isPrime, 7);
    std::thread worker4(isPrime, 9);
    std::thread worker5(isPrime, 11);
    std::thread worker6(isPrime, 13);
    std::thread worker7(isPrime, 15);
    std::thread worker8(isPrime, 17);

    worker1.join();
    worker2.join();
    worker3.join();
    worker4.join();
    worker5.join();
    worker6.join();
    worker7.join();
    worker8.join();

    std::sort(maxPrimes.begin(), maxPrimes.end());

    auto stop = high_resolution_clock::now();
    std::chrono::duration<double> diff = stop - start;
    std::cout << diff.count() << "s " << totalPrimes << " " << primeSum << std::endl;
    for (int i = maxPrimes.size() - 10; i < maxPrimes.size(); i++) {
        std::cout << maxPrimes[i] << " ";
    }
 }
