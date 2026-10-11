*This project has been created as part of the 42 curriculum by smeza-ro.*

# Codexion

## Description

Codexion is a multithreaded C simulation in which each coder repeatedly compiles, debugs, and refactors. A coder must acquire both neighboring dongles to compile. The simulation supports FIFO and earliest-deadline-first (EDF) scheduling, a per-dongle cooldown, a required compile count, and a monitor that ends the run when a coder burns out or everyone reaches the required count.

## Instructions

Build with the included Makefile and a C compiler with POSIX threads support:

```sh
make
```

Run the executable with exactly eight arguments, in this order:

```text
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor required_compiles dongle_cooldown scheduler
```

Times are in milliseconds. The number of coders, burnout time, compile time, and required compile count must be positive. Debug and refactor durations and the dongle cooldown may be zero. The scheduler must be `fifo` or `edf`.

For example:

```sh
./codexion 5 800 150 100 100 3 50 fifo
```

Use `make clean` to remove object files, `make fclean` to also remove the executable, or `make re` to rebuild from scratch.

## Blocking cases handled

- **Deadlock and Coffman's conditions:** A coder requests both dongles as a pair. The implementation takes both dongle mutexes in ascending dongle-ID order, checks both resources, and marks both unavailable before releasing either mutex. It does not let a coder hold one dongle while waiting for the other, preventing hold-and-wait; consistent lock ordering prevents circular wait. Mutual exclusion remains necessary to protect each dongle.
- **Scheduling and starvation risk:** Each dongle tracks pending requests. FIFO leaves requests in arrival order. EDF prioritizes the requester with the earlier burnout deadline (`last_compile + time_to_burnout`), with coder ID as a tie-breaker. FIFO preserves queue order and EDF favors urgency, but EDF does not provide a general formal starvation bound.
- **Cooldown:** A released dongle records its release time. It is eligible again only once the configured cooldown has elapsed; a coder must find both neighboring dongles eligible at the same time before acquiring either.
- **Burnout detection:** The monitor reads each coder's last compile timestamp and completed count under that coder's mutex. It declares burnout when the burnout deadline is reached and the coder has not completed the required number of compiles. The monitor checks periodically (every 500 microseconds); elapsed-time timestamps are measured in milliseconds.
- **Log serialization and shutdown:** A shared mutex serializes status output and protects the stop/burnout flags. Once the monitor detects burnout or completion, it sets the stop state and broadcasts on the dongle condition variables so condition waiters can wake and exit.
- **Single-coder edge case:** A dedicated routine waits on its dongle condition variable because one coder cannot acquire two distinct neighboring dongles.

## Thread synchronization mechanisms

- **`pthread_mutex_t` per dongle:** Protects dongle availability, release time, request queue, and the associated condition-variable protocol. Pair acquisition locks both dongles in ID order and updates both availability states while holding both locks, so two coders cannot claim an overlapping resource based on stale availability. Release updates each dongle while holding its mutex.
- **`pthread_cond_t` per dongle:** Release and monitor shutdown broadcast on the condition variable while holding the dongle mutex. The single-coder edge-case routine waits on this condition variable and rechecks the stop state after waking. The ordinary multi-coder acquisition loop currently retries availability checks with short sleeps rather than waiting on these conditions.
- **`pthread_mutex_t` per coder:** Protects compile-count updates and the monitor's reads of the compile count and last-compile timestamp. For example, the monitor copies both values while holding `m_coder`. Some worker-side reads of `compiles` are not protected by this mutex in the current implementation.
- **Shared logging/state mutex:** `m_log` serializes complete log lines and guards reads and writes of `stop_flag`; burnout declaration sets `burnout_flag` while holding it. Worker routines check `stop_flag` through `is_stopped` before continuing. Their direct reads of `burnout_flag` are not protected by `m_log`, so those reads are not synchronized with the monitor's write. The monitor otherwise communicates termination through the shared stop state and dongle condition broadcasts; there is no separate event object or event library in this implementation.

## Resources

- [POSIX threads: `pthread_mutex_lock`](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html) and [condition variables: `pthread_cond_wait`](https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html)
- E. W. Dijkstra, [Hierarchical ordering of sequential processes](https://www.cs.utexas.edu/~EWD/ewd03xx/EWD315.PDF), a classic discussion of concurrency and resource ordering.
- E. G. Coffman, M. J. Elphick, and A. Shoshani, [System Deadlocks](https://dl.acm.org/doi/10.1145/356586.356588), on deadlock conditions and prevention.
- C. L. Liu and J. W. Layland, [Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment](https://doi.org/10.1145/321738.321743), a foundational reference for deadline-based scheduling.

**AI use:** AI assistance was used to inspect the existing source and draft this README, including the build/run instructions and explanations of the synchronization and scheduling behavior. No project source code was generated or modified by that assistance for this documentation task.