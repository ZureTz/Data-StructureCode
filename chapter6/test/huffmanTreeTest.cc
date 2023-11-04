#include "huffman_tree.h"
#include <iomanip>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>
using std::cout;

size_t getHeight(HuffmanNode *root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

std::deque<std::deque<std::pair<char, int>>>
treeTable(HuffmanNode *root, const size_t height,
          const size_t currentIndex = 0) {
  if (root == nullptr) {
    return std::deque<std::deque<std::pair<char, int>>>();
  }

  std::deque<std::deque<std::pair<char, int>>> leftResult =
      treeTable(root->left, height, currentIndex + 1);

  std::deque<std::deque<std::pair<char, int>>> result(
      1, std::deque<std::pair<char, int>>(height, {'\0', 0}));
  result[0][currentIndex].first =
      (root->element.has_value() ? root->element.value() : '#');
  result[0][currentIndex].second = root->frequencyCount;

  std::deque<std::deque<std::pair<char, int>>> rightResult =
      treeTable(root->right, height, currentIndex + 1);

  result.insert(result.begin(), rightResult.begin(), rightResult.end());
  result.insert(result.end(), leftResult.begin(), leftResult.end());

  return result;
}

void printTreeAsTable(HuffmanNode *root) {
  if (root == nullptr) {
    return;
  }
  const size_t height = getHeight(root);
  const auto result = treeTable(root, height);
  for (const auto row : result) {
    for (const auto data : row) {
      if (data.first == '\0') {
        cout << "      ";
        continue;
      }
      cout << data.first << ',' << std::setw(3) << std::setfill(' ')
           << data.second << ' ';
    }
    cout << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  cout << "--------------------------------------------------------------------"
          "------------"
       << std::endl;

  HuffmanTree tree{
      {'A', 6},  {'B', 21}, {'C', 3}, {'D', 9},  {'E', 12},
      {'F', 18}, {'G', 38}, {'H', 4}, {'I', 11},
  };

  // printTreeAsTable(tree.root);
  tree.printFinalMap(cout);
  cout << "Full length of the string in bit: " << tree.fullLength()
       << std::endl;

  cout << "--------------------------------------------------------------------"
          "------------"
       << std::endl;

  HuffmanTree tree2(
      "The original justification for adding SIMD instructions to existing "
      "architectures was that many microprocessors were connected to graphics "
      "displays in PCs and workstations, so an increasing fraction of "
      "processing time was used for graphics. As Moore's Law increased the "
      "number of transistors available to microprocessors, it therefore made "
      "sense to improve graphics processing.A major driving force for "
      "improving graphics processing was the computer game industry, both on "
      "PCs and in dedicated game consoles such as the Sony PlayStation. The "
      "rapidly growing game market encouraged many companies to make "
      "increasing investments in developing faster graphics hardware, and this "
      "positive feedback loop led graphics processing to improve at a quicker "
      "rate than general-purpose processing in mainstream "
      "microprocessors.Given that the graphics and game community had "
      "different goals than the microprocessor development community, it "
      "evolved its own style of processing and terminology. As the graphics "
      "processors increased in power, they earned the name Graphics Processing "
      "Units or GPUs to distinguish themselves from CPUs.For a few hundred "
      "dollars, anyone can buy a GPU today with hundreds of parallel "
      "floating-point units, which makes high-performance computing more "
      "accessible. The interest in GPU computing blossomed when this potential "
      "was combined with a programming language that made GPUs easier to "
      "program. Hence, many programmers of scientific and multimedia "
      "applications today are pondering whether to use GPUs or CPUs.(This "
      "section concentrates on using GPUs for computing. To see how GPU "
      "computing combines with the traditional role of graphics acceleration, "
      "seeAppendix B.)Here are some of the key characteristics as to how GPUs "
      "vary from CPUs:n GPUs are accelerators that supplement a CPU, so they "
      "do not need to be able to perform all the tasks of a CPU. This role "
      "allows them to dedicate all their resources to graphics. It's fine for "
      "GPUs to perform some tasks poorly or not at all, given that in a system "
      "with both a CPU and a GPU, the CPU can do them if needed.n The GPU "
      "problem sizes are typically hundreds of megabytes to gigabytes, but not "
      "hundreds of gigabytes to terabytes.These differences led to different "
      "styles of architecture:n Perhaps the biggest difference is that GPUs do "
      "not rely on multilevel caches to overcome the long latency to memory, "
      "as do CPUs. Instead, GPUs rely on hardware multithreading (Section 6.4) "
      "to hide the latency to memory. That is, between the time of a memory "
      "request and the time that data arrive, the GPU executes hundreds or "
      "thousands of threads that are independent of that request."
      "The GPU memory is thus oriented toward bandwidth rather than latency. "
      "There are even special graphics DRAM chips for GPUs that are wider and "
      "have higher bandwidth than DRAM chips for CPUs. In addition, GPU "
      "memories have traditionally had smaller main memories than conventional "
      "microprocessors. In 2013, GPUs typically have 4 to 6 GiB or less, while "
      "CPUs have 32 to 256 GiB. Finally, keep in mind that for general-purpose "
      "computation, you must include the time to transfer the data between CPU "
      "memory and GPU memory, since the GPU is a coprocessor.n Given the "
      "reliance on many threads to deliver good memory bandwidth, GPUs can "
      "accommodate many parallel processors (MIMD) as well as many threads. "
      "Hence, each GPU processor is more highly multithreaded than a typical "
      "CPU, plus they have more processors.Although GPUs were designed for a "
      "narrower set of applications, some programmers wondered if they could "
      "specify their applications in a form that would let them tap the high "
      "potential performance of GPUs. After tiring of trying to specify their "
      "problems using the graphics APIs and languages, they developed "
      "C-inspired programming languages to allow them to write programs "
      "directly for the GPUs. An example is NVIDIA's CUDA (Compute Unified "
      "Device Architecture), which enables the programmer to write C programs "
      "to execute on GPUs, albeit with some restrictions. Appendix B gives "
      "examples of CUDA code. (OpenCL is a multi-company initiative to develop "
      "a portable programming language that provides many of the benefits of "
      "CUDA.)NVIDIA decided that the unifying theme of all these forms of "
      "parallelism is the CUDA Thread. Using this lowest level of parallelism "
      "as the programming primitive, the compiler and the hardware can gang "
      "thousands of CUDA threads together to utilize the various styles of "
      "parallelism within a GPU: multithreading, MIMD, SIMD, and "
      "instruction-level parallelism. These threads are blocked together and "
      "executed in groups of 32 at a time. A multithreaded processor inside a "
      "GPU executes these blocks of threads, and a GPU consists of 8 to 32 of "
      "these multithreaded processors.We use NVIDIA systems as our example as "
      "they are representative of GPU architectures. Specifically, we follow "
      "the terminology of the CUDA parallel programming language and use the "
      "Fermi architecture as the example.Like vector architectures, GPUs work "
      "well only with data-level parallel problems. Both styles have "
      "gather-scatter data transfers, and GPU processors have even "
      "moreregisters than do vector processors. Unlike most vector "
      "architectures, GPUs also rely on hardware multithreading within a "
      "single multithreaded SIMD processor to hide memory latency (see Section "
      "6.4).A multithreaded SIMD processor is similar to a vector processor, "
      "but the former has many parallel functional units instead of just a few "
      "that are deeply pipelined, as does the latter.As mentioned above, a GPU "
      "contains a collection of multithreaded SIMD processors; that is, a GPU "
      "is a MIMD composed of multithreaded SIMD processors. For example, "
      "NVIDIA has four implementations of the Fermi architecture at different "
      "price points with 7, 11, 14, or 15 multithreaded SIMD processors. To "
      "provide transparent scalability across models of GPUs with differing "
      "number of multithreaded SIMD processors, the Thread Block Scheduler "
      "hardware assigns blocks of threads to multithreaded SIMD processors. "
      "Figure 6.9 shows a simplified block diagram of a multithreaded SIMD "
      "processor.Dropping down one more level of detail, the machine object "
      "that the hardware creates, manages, schedules, and executes is a thread "
      "of SIMD instructions, which we will also call a SIMD thread. It is a "
      "traditional thread, but it contains exclusively SIMD instructions. "
      "These SIMD threads have their own program counters, and they run on a "
      "multithreaded SIMD processor. The SIMD Thread Scheduler includes a "
      "controller that lets it know which threads of SIMD instructions are "
      "ready to run, and then it sends them off to a dispatch unit to be run "
      "on the multithreadedSIMD processor. It is identical to a hardware "
      "thread scheduler in a traditional multithreaded processor (see Section "
      "6.4), except that it is scheduling threads of SIMD instructions. Thus, "
      "GPU hardware has two levels of hardware schedulers:1. The Thread Block "
      "Scheduler that assigns blocks of threads to multithreaded SIMD "
      "processors, and2. The SIMD Thread Scheduler within a SIMD processor, "
      "which schedules when SIMD threads should run.The SIMD instructions of "
      "these threads are 32 wide, so each thread of SIMD instructions would "
      "compute 32 of the elements of the computation. Since the thread "
      "consists of SIMD instructions, the SIMD processor must have parallel "
      "functional units to perform the operation. We call them SIMD Lanes, and "
      "they are quite similar to the Vector Lanes in Section 6.3.Elaboration: "
      "The number of lanes per SIMD processor varies across GPU generations. "
      "With Fermi, each 32-wide thread of SIMD instructions is mapped to 16 "
      "SIMD lanes, so each SIMD instruction in a thread of SIMD instructions "
      "takes two clock cycles to complete. Each thread of SIMD instructions is "
      "executed in lock step. Staying with the analogy of a SIMD processor as "
      "a vector processor, you could say that it has 16 lanes, and the vector "
      "length would be 32. This wide but shallow nature is why we use the term "
      "SIMD processor instead of vector processor, as it is more "
      "intuitive.Since by definition the threads of SIMD instructions are "
      "independent, the SIMD Thread Scheduler can pick whatever thread of SIMD "
      "instructions is ready, and need not stick with the next SIMD "
      "instruction in the sequence within a single thread. Thus, using the "
      "terminology of Section 6.4, it uses fine-grained multithreading.To hold "
      "these memory elements, a Fermi SIMD processor has an impressive 32,768 "
      "32-bit registers. Just like a vector processor, these registers are "
      "divided logically across the vector lanes or, in this case, SIMD lanes. "
      "Each SIMD thread is limited to no more than 64 registers, so you might "
      "think of a SIMD thread as having up to 64 vector registers, with each "
      "vector register having 32 elements and each element being 32 bits "
      "wide.Since Fermi has 16 SIMD lanes, each contains 2048 registers. Each "
      "CUDA thread gets one element of each of the vector registers. Note that "
      "a CUDA thread is just a vertical cut of a thread of SIMD instructions, "
      "corresponding to one element executed by one SIMD lane. Beware that "
      "CUDA threads are very different from POSIX threads; you can't make "
      "arbitrary system calls or synchronize arbitrarily in a CUDA thread.");

  // printTreeAsTable(tree2.root);
  tree2.printFinalMap(cout);
  cout << "Full length of the string in bit: " << tree2.fullLength()
       << std::endl;
  cout << "--------------------------------------------------------------------"
          "------------"
       << std::endl;

  HuffmanTree englishCharSet{
      {'A', 819}, {'B', 147}, {'C', 383}, {'D', 391}, {'E', 1225}, {'F', 226},
      {'G', 171}, {'H', 457}, {'I', 710}, {'J', 14},  {'K', 41},   {'L', 377},
      {'M', 334}, {'N', 706}, {'O', 726}, {'P', 289}, {'Q', 9},    {'R', 685},
      {'S', 636}, {'T', 941}, {'U', 258}, {'V', 109}, {'W', 159},  {'X', 21},
      {'Y', 158}, {'Z', 8},
  };
  englishCharSet.printFinalMap(cout);
  cout << "Full length of the string in bit: " << englishCharSet.fullLength()
       << std::endl;
  cout << "--------------------------------------------------------------------"
          "------------"
       << std::endl;

  return 0;
}