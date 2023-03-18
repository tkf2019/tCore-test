#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "uintr.h"

unsigned int uintr_received;
unsigned int uintr_fd;

uint64_t uintr_handler(struct __uintr_frame *ui_frame, uint64_t irqs) {
  printf("\t-- User Interrupt handler --\n");

  // read pending bits
  printf("\tPending User Interrupts: %lx\n", irqs);

  uintr_received = 1;

  return 0;
}

int main() {
  printf("Basic test: uipi_sample\n");

  pthread_t pt;
  int ret;

  if (uintr_register_receiver(uintr_handler)) {
    printf("Interrupt handler register error\n");
    exit(EXIT_FAILURE);
  }

  ret = uintr_create_fd(1);
  if (ret < 0) {
    printf("Interrupt vector allocation error\n");
    exit(EXIT_FAILURE);
  }

  printf("Success\n");
  exit(EXIT_SUCCESS);
}