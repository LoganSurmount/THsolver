# CPP Texas Solver

[![release](https://img.shields.io/github/v/release/bupticybee/TexasSolver?style=flat-square)](https://github.com/bupticybee/TexasSolver/releases)
[![license](https://img.shields.io/github/license/bupticybee/TexasSolver?style=flat-square)](https://github.com/bupticybee/TexasSolver/blob/master/LICENSE)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/bupticybee/TexasSolver/blob/console/TexasSolverTechDemo.ipynb)
[![Gitter chat](https://badges.gitter.im/gitterHQ/gitter.png)](https://gitter.im/TexasSolver/TexasSolver)

README [English](README.md) | [中文](README.zh-CN.md)

## Introduction 
A open sourced, extremely efficient Texas Hold'em and short deck solver. See this [Introduction video](https://youtu.be/IsSJNz7sRmQ) for more. Supports Windows,MacOs and Linux.

![](imgs/solver_example.gif)

<img width="1280" alt="image" src="https://github.com/LoganSurmount/THsolver/assets/80961905/35f9f87d-8258-448f-a8a0-4f1435b38b0f">

Features:

- In a tree with 1~2bets + allin, it's speed exceeds piosolver on flop
- Support Mac, Linux and Windows
- Support texas holdem and shortdeck
- Support cross language calls
- Result aliged with piosolver
- Support dump strategy to json file
- It's the c++ version of [TexasHoldemSolverJava](https://github.com/bupticybee/TexasHoldemSolverJava) with a ton of optimization, it's 5x faster than the java version and takes less than 1/3 memory.

Feel free to mess with a toy solver [in google colab](https://colab.research.google.com/github/bupticybee/TexasSolver/blob/console/TexasSolverTechDemo.ipynb)


## Install

Download package according to your OS in [release package](https://github.com/bupticybee/TexasSolver/releases), unzip it, and install is done. It's that simple.

## GUI version Usage

After install the solver, double click the application binary (TexasSolverGui.exe in windows or TexasSolverGui.app in MacOS) to run TexasSolver.

## Console version Usage

Please check [console version document](https://github.com/bupticybee/TexasSolver/tree/console#usage) for more.

## Speed benchmark with piosolver

Piosolver and my TexasSolver(console version) run use the same settings (spr=10,flop game) and their result are aligned.

|                                | Input config                                              | log                                                          | thread number | memory usage | accuracy | converge time |
| ------------------------------ | --------------------------------------------------------- | ------------------------------------------------------------ | ------------- | ------------ | -------- | ------------- |
| piosolver 1.0                  | [config_piosolver](benchmark/benchmark_piosolver.txt)     | [log_piosolver](benchmark/benchmark_outputs/piosolver_log.txt) | 6             | 492Mb        | 0.29%    | 242s          |
| TexasSolver 0.1.0 (Our solver) | [config_texassolver](benchmark/benchmark_texassolver.txt) | [log_texassolver](benchmark/benchmark_outputs/texassolver_log.txt) | 6             | 1600Mb       | 0.275%   | 172s          |

The compare image of their results is  [here](benchmark/benchmark_outputs/result_compair.png). As you can see their result are very close.

# License

[GNU AGPL v3](https://www.gnu.org/licenses/agpl-3.0.en.html)
