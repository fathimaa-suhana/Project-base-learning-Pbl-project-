# Week 4: Deadlock Simulation — Test Cases

This document contains sample test cases used to verify the Deadlock Simulation System and for explanation during the OS lab evaluation/viva.

---

## Test Case 1: Safe State (Banker's Algorithm Verification)

### Description
A standard 5-process, 3-resource type configuration from textbook Operating System concepts (Silberschatz). Demonstrates how the system determines whether resources can be allocated without causing a deadlock.

### Inputs
* **Number of Processes:** 5 ($P_0, P_1, P_2, P_3, P_4$)
* **Number of Resource Types:** 3 ($R_0, R_1, R_2$)
* **Available Vector:**
  ```text
  R0: 3,  R1: 3,  R2: 2
  ```
* **Allocation Matrix:**
  | Process | R0 | R1 | R2 |
  |---|---:|---:|---:|
  | P0 | 0 | 1 | 0 |
  | P1 | 2 | 0 | 0 |
  | P2 | 3 | 0 | 2 |
  | P3 | 2 | 1 | 1 |
  | P4 | 0 | 0 | 2 |

* **Maximum Matrix:**
  | Process | R0 | R1 | R2 |
  |---|---:|---:|---:|
  | P0 | 7 | 5 | 3 |
  | P1 | 3 | 2 | 2 |
  | P2 | 9 | 0 | 2 |
  | P3 | 2 | 2 | 2 |
  | P4 | 4 | 3 | 3 |

### Calculated Need Matrix ($Need = Maximum - Allocation$)
| Process | R0 | R1 | R2 |
|---|---:|---:|---:|
| P0 | 7 | 4 | 3 |
| P1 | 1 | 2 | 2 |
| P2 | 6 | 0 | 0 |
| P3 | 0 | 1 | 1 |
| P4 | 4 | 3 | 1 |

### Expected Output
* **System State:** `SAFE`
* **Safe Sequence:** `P1 -> P3 -> P4 -> P0 -> P2`
* **Verification Steps:**
  1. $Work = [3, 3, 2]$. $Need(P1) = [1, 2, 2] \le Work \implies P1$ finishes, new $Work = [3+2, 3+0, 2+0] = [5, 3, 2]$.
  2. $Need(P3) = [0, 1, 1] \le Work \implies P3$ finishes, new $Work = [5+2, 3+1, 2+1] = [7, 4, 3]$.
  3. $Need(P4) = [4, 3, 1] \le Work \implies P4$ finishes, new $Work = [7+0, 4+0, 3+2] = [7, 4, 5]$.
  4. $Need(P0) = [7, 4, 3] \le Work \implies P0$ finishes, new $Work = [7+0, 4+1, 5+0] = [7, 5, 5]$.
  5. $Need(P2) = [6, 0, 0] \le Work \implies P2$ finishes, new $Work = [7+3, 5+0, 5+2] = [10, 5, 7]$.
  6. All processes finished successfully.

---

## Test Case 2: Deadlock Detection & Recovery

### Description
Simulates a classic circular wait between two processes where each process holds one resource and waits for the resource held by the other.

### Inputs
* **Number of Processes:** 2 ($P_0, P_1$)
* **Number of Resource Types:** 2 ($R_0, R_1$)
* **Available Vector:** `[0, 0]`
* **Allocation Matrix:**
  | Process | R0 | R1 |
  |---|---:|---:|
  | P0 | 1 | 0 |
  | P1 | 0 | 1 |

* **Pending Requests (Waiting):**
  * $P_0$ is waiting for $R_1$: `[0, 1]`
  * $P_1$ is waiting for $R_0$: `[1, 0]`

### Expected Output
* **System State:** `DEADLOCKED`
* **Deadlocked Processes:** $P_0, P_1$
* **RAG Canvas:** Circular arrows between $P_0, R_1, P_1, R_0$ with processes highlighted in red.
* **Recovery Action:**
  * Click **10. Recover from Deadlock**.
  * The simulator selects the lowest-cost process to terminate ($P_0$).
  * $P_0$'s held resources are reclaimed back into `Available`.
  * $P_1$'s waiting request is satisfied and granted.
  * System state recovers from deadlock.

---

## Test Case 3: Resource Request (Safe vs. Unsafe Request)

### Description
Tests how the operating system handles a dynamic resource request using Banker's Algorithm.

### Steps
1. Load **Test Case 1 (Safe State)**.
2. Select **Process:** $P_1$ and **Request Vector:** `1 0 2`.
3. Click **Request**:
   * Condition 1: $Request \le Need(P_1) \implies [1, 0, 2] \le [1, 2, 2]$ (True).
   * Condition 2: $Request \le Available \implies [1, 0, 2] \le [3, 3, 2]$ (True).
   * Simulated Allocation: $Available$ becomes $[2, 3, 0]$, $Allocation(P_1)$ becomes $[3, 0, 2]$.
   * Safety check verifies a safe sequence still exists (`P1 -> P3 -> P4 -> P0 -> P2`).
   * **Result:** Request is **GRANTED**.
4. Now select $P_4$ and request `3 3 0`:
   * $Request > Available$ ($[3, 3, 0] > [2, 3, 0]$).
   * **Result:** $P_4$ is **BLOCKED (waiting)**. No unsafe allocation occurs.

