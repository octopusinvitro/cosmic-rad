# Cosmic Radiation Lab

My old lab class about cosmic radiation for Experimental Nuclear Physics undergraduate students.

Contains some macros to calculate radioactive source efficiencies (`mcEff`), fit parameters (`gauss` and `wmean`), and the confidence level of the fits (`cl`).

## The lab guide

The theory and lab techniques are explained in the lab-guide `cosmicrad.pdf`. LaTeX files for this document are provided. This is my first attempt to design a layout for a document in LaTeX. To compile, type:

```bash
$ . cosmicrad
```

Feel free to edit this work and add any improvements.

## The snippets

The code is explained in [http://cosmicrad.tk](http://cosmicrad.tk). It uses some snippets of code from the good ol' **Numerical Recipes** [http://www.nr.com/](http://www.nr.com/).

### Compile:

 * C programs:

```bash
$ gcc filename.c -o filename -lm
```

 * C++ programs:

```bash
$ g++ filename.cpp -o filename
```

### Run:

```bash
$ ./filename
```

## Licenses

All code is [MIT licensed](http://opensource.org/licenses/MIT).
The lab-guide is licensed [CC BY-NC 4.0](http://creativecommons.org/licenses/by-nc/4.0/legalcode).
