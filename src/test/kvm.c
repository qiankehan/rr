/* -*- Mode: C; tab-width: 8; c-basic-offset: 2; indent-tabs-mode: nil; -*- */

#include "util.h"
#include <linux/kvm.h>

int main(void) {
    int fd = open("/dev/kvm", O_RDWR);
    if (fd < 0) {
        atomic_puts("Can't open kvm device, aborting test");
        atomic_puts("EXIT-SUCCESS");
        return 0;
    }
    atomic_puts("Kvm device is opened");

    // KVM_GET_MSR_INDEX_LIST
	struct kvm_msr_list *msr_list;
    ALLOCATE_GUARD(msr_list, 0);
    test_assert(ioctl(fd, KVM_GET_MSR_INDEX_LIST, msr_list) == 0);
    VERIFY_GUARD(msr_list);

    // KVM_GET_MSR_FEATURE_INDEX_LIST
    msr_list->nmsrs = 0;
    test_assert(ioctl(fd, KVM_GET_MSR_FEATURE_INDEX_LIST, msr_list) == 0);
    VERIFY_GUARD(msr_list);

    atomic_puts("EXIT-SUCCESS");
    return 0;
}
