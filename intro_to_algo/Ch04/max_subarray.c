/*
Author: Kumar Shubham
Find Max subarray using divide and conquer method ...

*/


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>     // INT_MIN

typedef struct __max_sub_arr{
    int low;
    int high;
    int sum;
}msubarr;

void init(msubarr *m, int low, int high, int sum) {
    m->low = low;
    m->high = high;
    m->sum = sum;
}

msubarr max_sub_crossing(msubarr m, int a[]){
    int mid = (m.low + m.high)/2;

    msubarr cross;

    int i;
    int left_sum = INT_MIN;
    int right_sum = INT_MIN;
    int max_left, max_right;

    int sum = 0;

    for(i=mid;i>=m.low;i--) {
        sum += a[i];
        if(sum >= left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    sum = 0;

    for(i=mid+1;i<=m.high;i++){
        sum += a[i];
        if(sum >= right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }

    cross.low = max_left;
    cross.high = max_right;
    cross.sum = left_sum + right_sum;
    return cross;
}

msubarr max_sub_array(msubarr msa, int a[]) {
    int mid = 0;
    if(msa.low == msa.high)
        return msa;
    
    else {
        msubarr left, right, cross;
        left = msa;
        right = msa;
        mid = (msa.low + msa.high)/2;
        left.high = mid;
        right.low = mid+1;
        left = max_sub_array(left, a);
        right = max_sub_array(right, a);
        cross = max_sub_crossing(msa, a);

        if(left.sum >= right.sum && left.sum >=cross.sum)
            return left;
        else if (right.sum >= left.sum && right.sum>=cross.sum)
            return right;
        else
            return cross;
    }
}

int main() {

    msubarr input, res;
    int len;
    //int a[] = {-2, -5, 6, -2, -3, 1, 5, -6};
    int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

    len = sizeof(a)/sizeof(a[0]);
    init(&input, 0, len-1, 0);

    res = max_sub_array(input, a);

    printf("max sum: %i\n", res.sum);
    printf("subarray index %i to %i\n", res.low, res.high);

    return 0;
}
