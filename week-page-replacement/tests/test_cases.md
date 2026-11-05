# Week 5: Page Replacement Algorithms — Test Cases

This document defines standard test cases used to evaluate the Page Replacement Simulator and to demonstrate the comparative analysis during the OS evaluation/viva.

---

## Test Case 1: PDF Specification Benchmark

### Description
The official test case provided in the project specification PDF (*Page Replacement Algorithms in Operating Systems*).

### Inputs
* **Page-Reference String:** `7 0 1 2 0 3 0 4 2 3`
* **Total Page References:** 10
* **Number of Frames:** 3

### Step-by-Step Simulation Table (FIFO)
| Request (#) | Page | Frame 1 | Frame 2 | Frame 3 | Status | Explanation |
|:---:|:---:|:---:|:---:|:---:|:---:|:---|
| 1 | 7 | 7 | — | — | **Fault** | Frame 1 empty, page 7 loaded |
| 2 | 0 | 7 | 0 | — | **Fault** | Frame 2 empty, page 0 loaded |
| 3 | 1 | 7 | 0 | 1 | **Fault** | Frame 3 empty, page 1 loaded |
| 4 | 2 | 2 | 0 | 1 | **Fault** | Frames full; page 7 (oldest) replaced with 2 |
| 5 | 0 | 2 | 0 | 1 | **Hit** | Page 0 already present in Frame 2 |
| 6 | 3 | 2 | 3 | 1 | **Fault** | Page 0 (oldest) replaced with 3 |
| 7 | 0 | 2 | 3 | 0 | **Fault** | Page 1 (oldest) replaced with 0 |
| 8 | 4 | 4 | 3 | 0 | **Fault** | Page 2 (oldest) replaced with 4 |
| 9 | 2 | 4 | 2 | 0 | **Fault** | Page 3 (oldest) replaced with 2 |
| 10 | 3 | 4 | 2 | 3 | **Fault** | Page 0 (oldest) replaced with 3 |

### Performance Summary (FIFO)
* **Total Page References:** 10
* **Total Page Hits:** 1
* **Total Page Faults:** 9
* **Hit Ratio:** $\frac{1}{10} \times 100 = 10.0\%$
* **Fault Ratio:** $\frac{9}{10} \times 100 = 90.0\%$

### Algorithm Comparison for Test Case 1
| Algorithm | Page Hits | Page Faults | Hit Ratio | Fault Ratio | Best Performer |
|---|:---:|:---:|:---:|:---:|:---:|
| **FIFO** | 1 | 9 | 10.0% | 90.0% | |
| **LRU** | 2 | 8 | 20.0% | 80.0% | |
| **Optimal** | 3 | 7 | 30.0% | 70.0% | **Yes (Minimal faults)** |

---

## Test Case 2: Temporal Locality (Working Set Scenario)

### Description
A reference string exhibiting high temporal locality, where recently accessed pages are likely to be accessed again in the near future.

### Inputs
* **Page-Reference String:** `1 2 3 2 1 5 2 1 6 2`
* **Total Page References:** 10
* **Number of Frames:** 3

### Algorithm Comparison
| Algorithm | Page Hits | Page Faults | Hit Ratio | Fault Ratio |
|---|:---:|:---:|:---:|:---:|
| **FIFO** | 5 | 5 | 50.0% | 50.0% |
| **LRU** | 5 | 5 | 50.0% | 50.0% |
| **Optimal** | 6 | 4 | 60.0% | 40.0% |

---

## Test Case 3: Alternating Reference Pattern

### Description
Tests edge behavior with a minimal alternating sequence in small memory.

### Inputs
* **Page-Reference String:** `1 2 1 2 1 2`
* **Total Page References:** 6
* **Number of Frames:** 2

### Expected Output
* Initial cold misses: Page 1 (Fault), Page 2 (Fault).
* Subsequent accesses: Page 1 (Hit), Page 2 (Hit), Page 1 (Hit), Page 2 (Hit).
* **Page Hits:** 4
* **Page Faults:** 2
* **Hit Ratio:** $66.7\%$
* **Fault Ratio:** $33.3\%$
* All three algorithms yield identical performance because the working set (pages 1 and 2) completely fits inside the 2 allocated frames.

