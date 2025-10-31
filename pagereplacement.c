//FCFS
#include <stdio.h>

int isPresent(int frame[], int k, int page) {
    for (int i = 0; i < k; i++) {
        if (frame[i] == page) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int p, f;
    printf("Enter no. of pages: ");
    scanf("%d", &p);

    int pages[p];
    printf("Enter pages: ");
    for (int i = 0; i < p; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter no of frames: ");
    scanf("%d", &f);

    int frame[f];
    for (int i = 0; i < f; i++) {
        frame[i] = -1;
    }

    int isHit = 1;
    int hitCount = 0, pageFaults = 0;
    int frame_idx = 0;

    for (int i = 0; i < p; i++) {
        isHit = 1;

        if (!isPresent(frame, f, pages[i])) {
            frame[frame_idx] = pages[i];
            frame_idx = (frame_idx + 1) % f;
            isHit = 0;
            pageFaults++;
        }

        printf("%d -> ", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frame[j] == -1) {
                printf("- ");
            } else {
                printf("%d ", frame[j]);
            }
        }

        if (isHit == 0) {
            printf("=> M");
        } else {
            printf("=> H");
        }
        printf("\n");
    }

    hitCount = p - pageFaults;
    printf("Page Faults = %d\n", pageFaults);
    printf("Hits = %d\n", hitCount);
    printf("Hit Ratio : %d/%d\n", hitCount, p);
    printf("Miss Ratio : %d/%d\n", pageFaults, p);

    return 0;
}


//LFU
#include <stdio.h>

int isPresent(int frame[], int k, int page) {
    for (int i = 0; i < k; i++) {
        if (frame[i] == page) {
            return 1;
        }
    }
    return 0;
}

int getLFUIndex(int frame[], int freq[], int f) {
    int min = freq[0], index = 0;
    for (int i = 1; i < f; i++) {
        if (freq[i] < min) {
            min = freq[i];
            index = i;
        }
    }
    return index;
}

int main() {
    int p, f;
    printf("Enter no. of pages: ");
    scanf("%d", &p);
    int pages[p];
    printf("Enter pages: ");
    for (int i = 0; i < p; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter no of frames: ");
    scanf("%d", &f);
    int frame[f], freq[f];
    for (int i = 0; i < f; i++) {
        frame[i] = -1;
        freq[i] = 0;
    }

    int pageFaults = 0, hitCount = 0;

    for (int i = 0; i < p; i++) {
        int page = pages[i];
        int hit = 0;

        for (int j = 0; j < f; j++) {
            if (frame[j] == page) {
                freq[j]++;
                hit = 1;
                break;
            }
        }

        if (!hit) {
            int replaced = 0;
            for (int j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    frame[j] = page;
                    freq[j] = 1;
                    replaced = 1;
                    break;
                }
            }

            if (!replaced) {
                int idx = getLFUIndex(frame, freq, f);
                frame[idx] = page;
                freq[idx] = 1;
            }

            pageFaults++;
        } else {
            hitCount++;
        }

        printf("%d -> ", page);
        for (int j = 0; j < f; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        if (hit)
            printf("=> H\n");
        else
            printf("=> M\n");
    }

    printf("Page Faults = %d\n", pageFaults);
    printf("Hits = %d\n", hitCount);
    printf("Hit Ratio: %d/%d\n", hitCount, p);
    printf("Miss Ratio: %d/%d\n", pageFaults, p);

    return 0;
}


//LRU

#include <stdio.h>

int isPresent(int frame[], int f, int page) {
    for (int i = 0; i < f; i++) {
        if (frame[i] == page)
            return 1;
    }
    return 0;
}

int getLRUIndex(int lastUsed[], int f) {
    int min = lastUsed[0], index = 0;
    for (int i = 1; i < f; i++) {
        if (lastUsed[i] < min) {
            min = lastUsed[i];
            index = i;
        }
    }
    return index;
}

int main() {
    int p, f, time = 0;
    printf("Enter no. of pages: ");
    scanf("%d", &p);
    int pages[p];
    printf("Enter pages: ");
    for (int i = 0; i < p; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter no of frames: ");
    scanf("%d", &f);
    int frame[f], lastUsed[f];
    for (int i = 0; i < f; i++) {
        frame[i] = -1;
        lastUsed[i] = 0;
    }

    int pageFaults = 0, hitCount = 0;

    for (int i = 0; i < p; i++) {
        int page = pages[i];
        int hit = 0;

        for (int j = 0; j < f; j++) {
            if (frame[j] == page) {
                hit = 1;
                lastUsed[j] = ++time;
                break;
            }
        }

        if (!hit) {
            int replaced = 0;
            for (int j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    frame[j] = page;
                    lastUsed[j] = ++time;
                    replaced = 1;
                    break;
                }
            }

            if (!replaced) {
                int idx = getLRUIndex(lastUsed, f);
                frame[idx] = page;
                lastUsed[idx] = ++time;
            }

            pageFaults++;
        } else {
            hitCount++;
        }

        printf("%d -> ", page);
        for (int j = 0; j < f; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        if (hit)
            printf("=> H\n");
        else
            printf("=> M\n");
    }

    printf("Page Faults = %d\n", pageFaults);
    printf("Hits = %d\n", hitCount);
    printf("Hit Ratio: %d/%d\n", hitCount, p);
    printf("Miss Ratio: %d/%d\n", pageFaults, p);

    return 0;
}

