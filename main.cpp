#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <random>
#include <functional>

using namespace std;
using namespace std::chrono;

/******GENERARE VECTOR RANDOM*******/
void generate_array(vector <long long>& v, long long n, long long maxx, long long minn = 0)
{
    srand(std::time(nullptr));
    for(long long i=0; i<n; i++)
        v[i] = (((long long)(int)rand() << 32) + (long long)(int)rand()) % (maxx - minn) + minn;
}

/*******RADIX SORT*******/

void Count(vector <long long> &v, long long n, long long pow, long long base)
{
    vector <long long> fin(n);
    vector <long long> cnt(base, 0);
    long long i;
    for(long long x : v)
        cnt[(x/pow)%base]++;
    for(i=1; i<base; i++)
        cnt[i] += cnt[i-1];
    for(i=n-1; i>=0; i--)
    {
        fin[cnt[(v[i]/pow)%base]-1] = v[i];
        cnt[(v[i]/pow)%base]--;
    }
    v = fin;
}

void radix_sort(vector <long long> &v, long long left, long long right, long long base=10)
{
    long long mx = v[0], pow, n = right - left + 1;
    for (long long x : v)
        if(x>mx)
            mx = x;
    for (pow = 1; mx/pow > 0; pow*=base)
        Count(v, n, pow, base);
}

/***********MERGE SORT************/

void Merge(vector <long long> &v, long long left, long long middle, long long right)
{
    ///The first half of the vector v: left -> middle
    ///The second half of the vector v: middle+1 -> right
    ///We will create a new vector to memorize the sorted combination of the two halves
    vector <long long> res(right - left + 1);
    long long i = left, j = middle + 1, k = 0;
    while(i <= middle && j <= right)
    {

        if(v[i] < v[j])
            res[k++]=v[i++];
        else
            res[k++]=v[j++];
    }
    while(i<=middle)
        res[k++]=v[i++];

    while(j<=right)
        res[k++]=v[j++];
    k = 0;
    for (i = left; i <= right; i++)
        v[i] = res[k++];
    // res.clear();


}
///VARIANTA RECURSIVA
void merge_sort_rec (vector <long long> &v, long long left, long long right, long long base = 10)
{
    if (left < right)
    {
        long long middle = left + (right - left) / 2;
        merge_sort_rec(v, left, middle);
        merge_sort_rec(v, middle + 1, right);
        Merge(v, left, middle, right);
    }
}

///VARIANTA ITERATIVA
void merge_sort_it(vector <long long> &v, long long left, long long right, long long base = 10)
{
    long long current_size, n = right-left+1, x1;
    for (current_size = 1; current_size < n-1; current_size += current_size)
    {
        for(x1 = 0; x1 < n; x1 += 2*current_size)
        {
            long long mid = (x1 + current_size - 1<n-1)? x1 + current_size - 1:n-1;
            long long x2 = (x1+2*current_size -1 < n-1) ? x1+2*current_size -1: n-1;
            Merge(v, x1, mid, x2);
        }
    }
}


/*********SHELL SORT*********/

void shell_sort_routine(vector <long long> &v, long long n, long long seq[])
{
    long long h;
    for(h=0; seq[h]>n; h++);
    for(; seq[h]>0; h++)
    {

        long long i;
        for(i = seq[h]; i< n; i++)
        {
            long long j, x = v[i];
            for(j=i; j>=seq[h] && v[j-seq[h]] > x; j-=seq[h])
                v[j] = v[j-seq[h]];
            v[j] = x;
        }
    }
}


void shell_sort_classic(vector <long long>& v, long long left, long long right, long long base = 10)
{
    long long h, i, n = right - left + 1;
    for(h = n/2; h>0; h/=2)
    {
        for(i=h; i<n; i++)
        {
            long long j, x = v[i];
            for(j=i; j>=h && v[j-h] > x; j-=h)
                v[j] = v[j-h];
            v[j] = x;
        }
    }
}

void shell_sort_1(vector <long long> &v, long long left, long long right, long long base = 10)
{
    long long n = right-left + 1;
    long long seq[] = {70223210512, 30095661648, 13166851971, 5138283696, 2085837936, 852913488, 343669872, 114556624, 49095696, 21479367, 8382192, 3402672, 1391376, 463792, 198768, 86961, 33936,13776, 4592,1968, 861, 336, 112, 48, 21, 7, 3, 1 };
    shell_sort_routine(v, n, seq);

}

void shell_sort_knuth(vector <long long>& v, long long left, long long right, long long base = 10)
{
    long long n = right-left+1;
    long long seq[] = {1270932914164, 423644304721, 141214768240, 47071589413, 15690529804, 5230176601, 1743392200, 581130733, 193710244, 64570081, 21523360, 7174453, 2391484, 797161, 265720, 88573, 29524, 9841, 3280, 1093, 364, 121, 40, 13, 4, 1};
    shell_sort_routine(v, n, seq);
}


void shell_sort_sedgewick(vector <long long>& v, long long left, long long right, long long base = 10)
{
    long long n = right-left+1;
    long long seq[] = {4398049656833, 1099513200641, 274878693377, 68719869953, 17180065793, 4295065601, 1073790977, 268460033,
                       67121153, 16783361, 4197377, 1050113, 262913, 65921, 16577, 4193, 1073, 281, 77, 23, 8, 1
                      };
    shell_sort_routine(v, n, seq);
}

void shell_sort_pratt(vector <long long>& v, long long left, long long right, long long base = 10)
{
    long long n = right-left+1;
    long long seq[] = {9795520512, 9663676416, 9298091736, 9172942848, 8707129344, 8589934592, 8264970432, 8153726976, 7739670528,
                       7346640384, 7247757312, 6973568802, 6879707136, 6530347008, 6442450944, 6198727824, 6115295232, 5804752896,
                       5509980288, 5435817984, 5159780352, 4897760256, 4831838208, 4649045868, 4586471424, 4353564672, 4294967296,
                       4132485216, 4076863488, 3869835264, 3673320192, 3623878656, 3486784401, 3439853568, 3265173504, 3221225472,
                       3099363912, 3057647616, 2902376448, 2754990144, 2717908992, 2579890176, 2448880128, 2415919104, 2324522934,
                       2293235712, 2176782336, 2147483648, 2066242608, 2038431744, 1934917632, 1836660096, 1811939328, 1719926784,
                       1632586752, 1610612736, 1549681956, 1528823808, 1451188224, 1377495072, 1358954496, 1289945088, 1224440064,
                       1207959552, 1162261467, 1146617856, 1088391168, 1073741824, 1033121304, 1019215872, 967458816, 918330048,
                       905969664, 859963392, 816293376, 805306368, 774840978, 764411904, 725594112, 688747536, 679477248, 644972544,
                       612220032, 603979776, 573308928, 544195584, 536870912, 516560652, 509607936, 483729408, 459165024, 452984832,
                       429981696, 408146688, 402653184, 387420489, 382205952, 362797056, 344373768, 339738624, 322486272, 306110016,
                       301989888, 286654464, 272097792, 268435456, 258280326, 254803968, 241864704, 229582512, 226492416, 214990848,
                       204073344, 201326592, 191102976, 181398528, 172186884, 169869312, 161243136, 153055008, 150994944, 143327232,
                       136048896, 134217728, 129140163, 127401984, 120932352, 114791256, 113246208, 107495424, 102036672, 100663296,
                       95551488, 90699264, 86093442, 84934656, 80621568, 76527504, 75497472, 71663616, 68024448, 67108864, 63700992,
                       60466176, 57395628, 56623104, 53747712, 51018336, 50331648, 47775744, 45349632, 43046721, 42467328, 40310784,
                       38263752, 37748736, 35831808, 34012224, 33554432, 31850496, 30233088, 28697814, 28311552, 26873856, 25509168,
                       25165824, 23887872, 22674816, 21233664, 20155392, 19131876, 18874368, 17915904, 17006112, 16777216, 15925248,
                       15116544, 14348907, 14155776, 13436928, 12754584, 12582912, 11943936, 11337408, 10616832, 10077696, 9565938,
                       9437184, 8957952, 8503056, 8388608, 7962624, 7558272, 7077888, 6718464, 6377292, 6291456, 5971968, 5668704,
                       5308416, 5038848, 4782969, 4718592, 4478976, 4251528, 4194304, 3981312, 3779136, 3538944, 3359232, 3188646,
                       3145728, 2985984, 2834352, 2654208, 2519424, 2359296, 2239488, 2125764, 2097152, 1990656, 1889568, 1769472,
                       1679616, 1594323, 1572864, 1492992, 1417176, 1327104, 1259712, 1179648, 1119744, 1062882, 1048576, 995328,
                       944784, 884736, 839808, 786432, 746496, 708588, 663552, 629856, 589824, 559872, 531441, 524288, 497664,
                       472392, 442368, 419904, 393216, 373248, 354294, 331776, 314928, 294912, 279936, 262144, 248832, 236196,
                       221184, 209952, 196608, 186624, 177147, 165888, 157464, 147456, 139968, 131072, 124416, 118098, 110592,
                       104976, 98304, 93312, 82944, 78732, 73728, 69984, 65536, 62208, 59049, 55296, 52488, 49152, 46656, 41472,
                       39366, 36864, 34992, 32768, 31104, 27648, 26244, 24576, 23328, 20736, 19683, 18432, 17496, 16384, 15552, 13824,
                       13122, 12288, 11664, 10368, 9216, 8748, 8192, 7776, 6912, 6561, 6144, 5832, 5184, 4608, 4374, 4096, 3888, 3456,
                       3072, 2916, 2592, 2304, 2187, 2048, 1944, 1728, 1536, 1458, 1296, 1152, 1024, 972, 864, 768, 729, 648, 576, 512,
                       486, 432, 384, 324, 288, 256, 243, 216, 192, 162, 144, 128, 108, 96, 81, 72, 64, 54, 48, 36, 32, 27, 24, 18, 16,
                       12, 9, 8, 6, 4, 3, 2, 1
                      };
    shell_sort_routine(v, n, seq);
}



/**********HEAP SORT******/

void max_heap_check(vector <long long>& v, long long n, long long i)
{
    long long l = i<<1;
    long long r = 1+l;
    long long root = i;
    if(l<n && v[l] > v[root])
        root = l;
    if(r<n && v[r]>v[root])
        root = r;
    if(root != i)
    {
        swap(v[i], v[root]);
        max_heap_check(v,n, root);
    }

}

void heapsort(vector <long long> & v, long long left, long long right, long long base = 10)
{
    long long i, n = right - left + 1;
    for(i = n/2-1; i>=0; i--)
        max_heap_check(v, n, i);
    for(i = n-1; i>0; i--)
    {
        swap(v[0], v[i]);
        max_heap_check(v, i, 0);
    }
}

///varianta bottom up
void bottom_up_reheap(vector <long long>& v, long long n, long long i)
{

    ///j = leaf-search(v, n, i)
    long long j = i;
    while(2*j<n-1)
    {
        if(v[2*j]>v[2*j+1])
            j = 2*j;
        else
            j = 2*j+1;
    }
    if (2*j == n-1) j = n-1;

    ///bottom-up search(i, j);
    while(v[i] > v[j])
        j /= 2;

    ///interchange(i, j), unde j = bottom-up serach(i, j)
    ///varianta 2
    long long x = v[j];
    v[j] = v[i];
    while(j > i)
    {
        swap(v[j/2], x);
        j /= 2;
    }
}

void heapsort_2(vector <long long> &v, long long left, long long right, long long base = 10)
{
    long long i, n = right - left + 1;
    for(i=n/2-1; i>=0; i--)
        bottom_up_reheap(v, n, i);
    for(i = n-1 ; i > 0; i--)
    {
        swap(v[0], v[i]);
        bottom_up_reheap(v, i, 0);
    }
}

/************QUICK SORT********/
void quicksort_1(vector <long long> &v, long long left, long long right, long long base=10)
{
    long long i, j, x;
    ///luam pivotul initial v[left]
    if(left < right)
    {
        long long middle = left + (right - left) / 2;
        x = v[left];
        v[left] = v[middle];
        v[middle] = x;
        i = left, j = right;
        long long k = 0;
        while(i<j)
        {
            if(v[i]>v[j])
            {
                x = v[i];
                v[i] = v[j];
                v[j] = x;
                k = 1-k;
            }
            i += k;
            j -= 1-k;
        }
        quicksort_1(v, left, i-1);
        quicksort_1(v, i+1, right);

    }
}

void three_way_quicksort(vector <long long> &v, long long left, long long right, long long base = 10)
{
    if(left>=right)
        return;
    long long i, j, l=left, r=right;
    if(right<left)
    {
        if(v[right]<v[left])
            swap(v[right], v[left]);
        i = left;
        j = right;
    }
    long long middle = left, pivot = v[right];
    while(middle<=right)
    {
        if(v[middle]<pivot)
        {
            swap(v[left], v[middle]);
            left++;
            middle++;
        }
        else if (v[middle] > pivot)
        {
            swap(v[middle], v[right]);
            right--;
        }
        else
            middle++;
    }
    i = left-1;
    j = middle;
    left = l;
    right = r;
    three_way_quicksort(v, left, i);
    three_way_quicksort(v, j, right);
}

void Mquicksort(vector <long long> &v, long long left, long long right, long long pivot) /// alegerea dinamica a pivotului (incercam sa-l alegem ai sa fie elemetele echilibrate de ambele parti)
{
    if(left<right)
    {
        long long i, z, j, x, Pivot1, Pivot2, K, CountLess = 0, SumLess = 0, CountLarger = 0, SumLarger = 0;
        i = z = left;
        j = x = right;
        K = v[right];
        bool ok = 1;
        while(i<=j)
        {
            if(v[i]<=pivot)
            {
                CountLess++;
                SumLess += v[i];
                if(ok == 1 && K>= pivot - v[i])
                    K = pivot - v[i];
                else
                    ok = 0;
                i++;
            }
            else
            {
                CountLarger++;
                SumLarger += v[i];
                swap(v[i], v[j]);
                j--;
            }
        }
        if(CountLess != 0)
        {
            Pivot1 = SumLess/CountLess;
            if(ok != 1)
                Mquicksort(v, z, i-1, Pivot1);
        }
        if(CountLarger!=0)
        {
            Pivot2 = SumLarger/CountLarger;
            Mquicksort(v, i, x, Pivot2);
        }

    }
}



long long median_5(vector <long long>& v, long long start)
{
    register long long v0 = v[start];
    register long long v1 = v[start+1];
    register long long v2 = v[start+2];
    register long long v3 = v[start+3];
    register long long v4 = v[start+4];
    if(v1<v0)
        swap(v0, v1);
    if(v2<v0)
        swap(v0, v2);
    if (v3 < v0)
        swap(v0, v3);
    if (v4 < v0)
        swap(v0, v4);
    if (v2 < v1)
        swap(v1, v2);
    if (v3 < v1)
        swap(v1, v3);
    if (v4 < v1)
        swap(v1, v4);
    if (v3 < v2)
        swap(v2, v3);
    if (v4 < v2)
        swap(v2, v4);
    if (v2 == v[start])
        return start;
    if (v2 == v[start+1])
        return start+1;
    if (v2 == v[start+2])
        return start+2;
    if (v2 == v[start+3])
        return start+3;
    if (v2 == v[start+4])
        return start+4;

}

long long partition(vector <long long> &v, long long n, long long pivot)
{
    long long x = v[pivot], k = 0, i;
    swap(v[pivot], v[n-1]);
    for(i = 0; i<n-1; i++)
    {
        if(v[i]<x)
        {
            swap(v[i], v[k]);
            k++;
        }
    }
    swap(v[k], v[n-1]);
    return k;

}


void five_way_quicksort(vector <long long> &v, long long left, long long right, long long bae=10)
{
    long long n = right-left+1;
    if(n<5)
    {
        long long i, j;
        for(i=left; i<=right; i++)
            for(j = i+1; j<=right; j++)
                if(v[j]<v[i])
                    swap(v[j], v[i]);
        return;
    }
    else
    {
        long long x = v[median_5(v, left)];
        long long l = left, r = left, u = right;
        swap(v[median_5(v, left)],  v[right]);
        while(r<=u)
        {
            if(v[r]<x)
            {
                swap(v[l], v[r]);
                l++;
                r++;
            }
            else if(v[r]>x)
            {
                swap(v[r], v[u]);
                u--;
            }
            else
                r++;
        }
        five_way_quicksort(v, left, l-1);
        five_way_quicksort(v, r, right);

    }
}


///final

bool check_sorted(vector <long long>& v, long long n)
{
    long long i;
    for(i=1; i<n; i++)
        if(v[i-1]>v[i])
            return 0;
    return 1;
}

bool check_with_stl(vector <long long>v, vector <long long>a, long long n)
{
    long long i;
    for(i=0; i<n; i++)
        if(v[i]!=a[i])
            return 0;
    return 1;
}
void afis(vector <long long> &v, long long n)
{
    for(long long i = 0; i<n; i++)
        cout<<v[i]<<' ';
    cout<<'\n';
}

void generate_cvs()
{
    ofstream fout("sort_times.cvs");
    //fout<<"n, STL, Radix(base10), Radix(base32), Radix(base65536)\n";
    //fout<<"n, STL, MergeSort(rec), MergeSort(it)\n";
    long long check = 0;
    //fout<<"n, STL, Heapsort, HeapSort_bottom_up\n";
    fout<<"n, STL, Quicksort, Quicksort(3), Quicksort(5)\n";
    for(long long n = 100000  ; n<=10000000; n+=100000 )
    {
        fout<<n<<',';
        vector <long long> test(n);
        generate_array(test, n, 9223372036854775807);
        vector <long long> copy = test;
        auto start_1 = system_clock::now();
        sort(test.begin(), test.end());
        auto stop_1 = system_clock::now();
        auto duration_1 = duration_cast<microseconds>(stop_1 - start_1);
        fout<<duration_1.count()<<',';
        //cout<<"Time taken to sort (stl) "<<duration_1.count()<<'\n';
        vector <long long>a = test;
        /*
                test = copy;
                auto start_2 = system_clock::now();
                //radix_sort(test, 0, n-1);
                //merge_sort_rec(test, 0, n-1);
                //shell_sort_classic(test, 0, n-1);
                heapsort(test, 0, n-1);
                auto stop_2 = system_clock::now();
                auto duration_2 = duration_cast<microseconds>(stop_2 - start_2);
                fout<<duration_2.count()<<',';
                check += check_with_stl(test, a, n);
                //cout << "Time taken to sort(rec): " <<duration_2.count() << " microseconds" << endl;

                test = copy;
                auto start_3 = system_clock::now();
                //radix_sort(test, 0, n-1, 32)
                //merge_sort_it(test, 0, n-1);
                //shell_sort_1(test, 0, n-1);
                heapsort_2(test, 0, n-1);
                auto stop_3 = system_clock::now();
                auto duration_3 = duration_cast<microseconds>(stop_3 - start_3);
                fout<<duration_3.count()<<'\n';
                //cout << "Time taken to sort(it): " <<duration_3.count() << " microseconds" << endl;
                check += check_with_stl(test, a, n);
        */
        test = copy;
        auto start_4 = system_clock::now();
        //radix_sort(test, 0, n-1, 65536);
        //shell_sort_knuth(test, 0, n-1);
        quicksort_1(test, 0, n-1);
        auto stop_4 = system_clock::now();
        auto duration_4 = duration_cast<microseconds>(stop_4 - start_4);
        fout<<duration_4.count()<<',';
        //cout << "Time taken to sort(q1): " <<duration_4.count() << " microseconds" << endl;
        //cout<<"\n";
        check += check_with_stl(test, a, n);

        test = copy;
        auto start_5 = system_clock::now();
        //radix_sort(test, 0, n-1, 65536);
        three_way_quicksort(test, 0, n-1);
        auto stop_5 = system_clock::now();
        auto duration_5 = duration_cast<microseconds>(stop_5 - start_5);
        fout<<duration_5.count()<<',';
        check += check_with_stl(test, a, n);

        test = copy;
        auto start_6 = system_clock::now();
        //radix_sort(test, 0, n-1, 65536);
        //shell_sort_sedgewick(test, 0, n-1);
        five_way_quicksort(test, 0, n-1);
        auto stop_6 = system_clock::now();
        auto duration_6 = duration_cast<microseconds>(stop_6 - start_6);
        fout<<duration_6.count()<<'\n';
        check += check_with_stl(test, a, n);
        /*
                test = copy;
                auto start_7 = system_clock::now();
                //radix_sort(test, 0, n-1, 65536);
                //shell_sort_pratt(test, 0, n-1);
                Mquicksort(test, 0, n-1, n-1);
                auto stop_7 = system_clock::now();
                auto duration_7 = duration_cast<microseconds>(stop_7 - start_7);
                fout<<duration_7.count()<<'\n';
                check += check_with_stl(test, a, n);

        */
    }

    cout<<check<<'\n';
}

void all_sorts(vector <long long>& v, long long n, long long maxx)
{
    vector <long long> copy = v;


    cout<<"----------------STL SORT----------------\n";
    auto start_1 = system_clock::now();
    sort(v.begin(), v.end());
    auto stop_1 = system_clock::now();
    auto duration_1 = duration_cast<microseconds>(stop_1 - start_1);
    cout << "Time taken to sort: " <<(float)duration_1.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    vector <long long> a = v;
    if(check_sorted(v, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<'\n';


    cout<<"-----------RADIX SORT(base 10)-----------\n";
    v = copy;
    auto start_2 = system_clock::now();
    radix_sort(v, 0, n-1);
    auto stop_2 = system_clock::now();
    auto duration_2 = duration_cast<microseconds>(stop_2 - start_2);
    cout << "Time taken to sort: " <<(float)duration_2.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------RADIX SORT(base 32)-----------\n";
    v = copy;
    auto start_3 = system_clock::now();
    radix_sort(v, 0, n-1, 32);
    auto stop_3 = system_clock::now();
    auto duration_3 = duration_cast<microseconds>(stop_3 - start_3);
    cout << "Time taken to sort: " <<(float)duration_3.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------RADIX SORT(base 2^16)-----------\n";
    v = copy;
    auto start_4 = system_clock::now();
    radix_sort(v, 0, n-1, 65536);
    auto stop_4 = system_clock::now();
    auto duration_4 = duration_cast<microseconds>(stop_4 - start_4);
    cout << "Time taken to sort: " <<(float)duration_4.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";


    cout<<"-----------MERGE SORT RECURSIVE-----------\n";
    v = copy;
    auto start_5 = system_clock::now();
    merge_sort_rec(v, 0, n-1);
    auto stop_5 = system_clock::now();
    auto duration_5 = duration_cast<microseconds>(stop_5 - start_5);
    cout << "Time taken to sort: " <<(float)duration_5.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------MERGE SORT ITERATIVE-----------\n";
    v = copy;
    auto start_6 = system_clock::now();
    merge_sort_rec(v, 0, n-1);
    auto stop_6 = system_clock::now();
    auto duration_6 = duration_cast<microseconds>(stop_6 - start_6);
    cout << "Time taken to sort: " <<(float)duration_6.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";


    cout<<"-----------SHELLSORT CLASSIC-----------\n";
    v = copy;
    auto start_7 = system_clock::now();
    shell_sort_classic(v, 0, n-1);
    auto stop_7 = system_clock::now();
    auto duration_7 = duration_cast<microseconds>(stop_7 - start_7);
    cout << "Time taken to sort: " <<(float)duration_7.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------SHELLSORT (1)-----------\n";
    v = copy;
    auto start_8 = system_clock::now();
    shell_sort_1(v, 0, n-1);
    auto stop_8 = system_clock::now();
    auto duration_8 = duration_cast<microseconds>(stop_8 - start_8);
    cout << "Time taken to sort: " <<(float)duration_8.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------SHELLSORT Knuth(1)-----------\n";
    v = copy;
    auto start_9 = system_clock::now();
    shell_sort_knuth(v, 0, n-1);
    auto stop_9 = system_clock::now();
    auto duration_9 = duration_cast<microseconds>(stop_9 - start_9);
    cout << "Time taken to sort: " <<(float)duration_9.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------SHELLSORT Sedgewick-----------\n";
    v = copy;
    auto start_11 = system_clock::now();
    shell_sort_sedgewick(v, 0, n-1);
    auto stop_11 = system_clock::now();
    auto duration_11 = duration_cast<microseconds>(stop_11 - start_11);
    cout << "Time taken to sort: " <<(float)duration_11.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------SHELLSORT Pratt-----------\n";
    v = copy;
    auto start_12 = system_clock::now();
    shell_sort_pratt(v, 0, n-1);
    auto stop_12 = system_clock::now();
    auto duration_12 = duration_cast<microseconds>(stop_12 - start_12);
    cout << "Time taken to sort: " <<(float)duration_12.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------HEAPSORT-----------\n";
    v = copy;
    auto start_13 = system_clock::now();
    heapsort(v, 0, n-1);
    auto stop_13 = system_clock::now();
    auto duration_13 = duration_cast<microseconds>(stop_13 - start_13);
    cout << "Time taken to sort: " <<(float)duration_13.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------HEAPSORT(bottom-up)-----------\n";
    v = copy;
    auto start_14 = system_clock::now();
    heapsort_2(v, 0, n-1);
    auto stop_14 = system_clock::now();
    auto duration_14 = duration_cast<microseconds>(stop_14 - start_14);
    cout << "Time taken to sort: " <<(float)duration_13.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";


    cout<<"-----------QUICKSORT(classic)-----------\n";
    v = copy;
    auto start_15 = system_clock::now();
    quicksort_1(v, 0, n-1);
    auto stop_15 = system_clock::now();
    auto duration_15 = duration_cast<microseconds>(stop_15 - start_15);
    cout << "Time taken to sort: " <<(float)duration_15.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------QUICKSORT(median of 3)-----------\n";
    v = copy;
    auto start_16 = system_clock::now();
    three_way_quicksort(v, 0, n-1);
    auto stop_16 = system_clock::now();
    auto duration_16 = duration_cast<microseconds>(stop_16 - start_16);
    cout << "Time taken to sort: " <<(float)duration_16.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------QUICKSORT(median of 5)-----------\n";
    v = copy;
    auto start_17 = system_clock::now();
    five_way_quicksort(v, 0, n-1);
    auto stop_17 = system_clock::now();
    auto duration_17 = duration_cast<microseconds>(stop_17 - start_17);
    cout << "Time taken to sort: " <<(float)duration_17.count()/1000 << " milliseconds" << endl;
    ///verify if the array is sorted
    if(check_sorted(v, n) && check_with_stl(v, a, n))
        cout<<"The array was sorted successfully!\n";
    else
        cout<<"Sorting unsuccessful!\n";
    cout<<"\n";

    cout<<"-----------QUICKSORT(dinamic pivot)-----------\n";
    v = copy;
    if(maxx <= 2000000000000)
    {
        auto start_18 = system_clock::now();
        Mquicksort(v, 0, n-1, 0);
        auto stop_18 = system_clock::now();
        auto duration_18 = duration_cast<microseconds>(stop_18 - start_18);
        cout << "Time taken to sort: " <<(float)duration_18.count()/1000 << " milliseconds" << endl;
        ///verify if the array is sorted
        if(check_sorted(v, n) && check_with_stl(v, a, n))
            cout<<"The array was sorted successfully!\n";
        else
            cout<<"Sorting unsuccessful!\n";
    }
    else
    {
        cout<<"The array is too big, unsortable!\n";
    }

    cout<<"\n";

}

int main()
{
    //generate_cvs();

    long long n, maxx;
    int nr_tests;
    char choice;
    cout<<"Number of tests: ";
    cin>>nr_tests;
    cout<<"\n";
    cout<<"Do you want to manually set the test-arrays?(y/n)\n";
    cin>>choice;

    if(choice == 'y')
    {
        for(int i = 1; i <= nr_tests; i++)
        {
            cout<<"TEST "<<i<<"\nNumber of elements: ";
            cin>>n;
            cout<<"Maximum value of the elements: ";
            cin>>maxx;
            vector <long long> v;
            long long x;
            cout<<"Elements: \n";
            for(int j=0; j < n; j++)
            {
                cin>>x;
                v[j]=x;
            }
            all_sorts(v, n, maxx);
        }
    }
    else
    {
        for(int i = 1; i <= nr_tests; i++)
        {
            cout<<"TEST "<<i<<"\nNumber of elements: ";
            cin>>n;
            cout<<"Maximum value of the elements: ";
            cin>>maxx;
            vector <long long> v(n);
            cout<<"Generating array...----------------";
            generate_array(v, n, maxx);
            cout<<"Done\n";
            all_sorts(v, n, maxx);
        }
    }
    return 0;
}
