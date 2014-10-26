**YED** is a library for numerically solving the physical problem of quantum Hall effect (QHE). It is designed to help researchers to save time in programming, and focus on the physics of fantastic quantum Hall effect. YED is a free software under GNU General Public License version 3.  

**YED** is mainly written in C++. It uses the concepts of object-oriented programming (**OOP**) to treat the different physical processes of QHE as C++ classes. To be specific, the C++ classes defined in **YED** are:
- basis: basis in the Fock space of the QHE problem;
- interaction: the specific interaction between particles in the QHE problem;
- matrix: matrix representation of the QHE problem;
- ED: exact diagonalization (ED) of the **matrix**;
- analysis: data analysis of the results of QHE calculation.  

At this point of time, **YED** can solve the QHE problems of finite size systems in the following geometries:
- disk;
- torus (rectangular lattice with different aspect ratios).


