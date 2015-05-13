#!/usr/bin/perl -w

use strict;
use File::Temp;

my @filenames = (
    #['Dense max-flow (C++)', 'MaxFlow.cc', 'Combinatorial optimization'],
    ['Sparse max-flow (C++)', 'Dinic.cc', 'Combinatorial optimization'],
    ['Min-cost max-flow (C++)', 'MinCostMaxFlow.cc', 'Combinatorial optimization'],
    ['Push-relabel max-flow (C++)', 'PushRelabel.cc', 'Combinatorial optimization'],
    ['Min-cost matching (C++)', 'MinCostMatching.cc', 'Combinatorial optimization'],
    ['Max bipartite matching (C++)', 'MaxBipartiteMatching.cc', 'Combinatorial optimization'],
    ['Global min cut (C++)', 'MinCut.cc', 'Combinatorial optimization'],
    ['Graph cut inference (C++)', 'GraphCutInference.cc', 'Combinatorial optimization'],
    #['Max-flow (Java)', 'MaxFlow.java', 'Combinatorial optimization'],
    #['Min-cost max-flow (Java)', 'MinCostMaxFlow.java', 'Combinatorial optimization'],

    ['Convex hull (C++)', 'ConvexHull.cc', 'Geometry'],
    ['Miscellaneous geometry (C++)', 'Geometry.cc', 'Geometry'],
    ['Java geometry (Java)', 'JavaGeometry.java', 'Geometry'],
    ['3D geometry (Java)', 'Geom3D.java', 'Geometry'],
    #['Slow Delaunay triangulation (Java)', 'Delaunay.java', 'Geometry'],
    ['Slow Delaunay triangulation (C++)', 'Delaunay.cc', 'Geometry'],

    ['Number theoretic algorithms (modular, Chinese remainder, linear Diophantine) (C++)', 'Euclid.cc', 'Numerical algorithms'],
    ['Systems of linear equations, matrix inverse, determinant (C++)', 'GaussJordan.cc', 'Numerical algorithms'],
    ['Reduced row echelon form, matrix rank (C++)', 'ReducedRowEchelonForm.cc', 'Numerical algorithms'],
    #['Fast Fourier transform (C++)', 'FFT.cc', 'Numerical algorithms'],
    ['Fast Fourier transform (C++)', 'FFT_new.cpp', 'Numerical algorithms'],
    ['Simplex algorithm (C++)', 'Simplex.cc', 'Numerical algorithms'],

    #['Bellman-Ford shortest paths with negative edge weights (C++)', 'BellmanFord.cc', 'Graph algorithms'],
    #['Dijkstra and Floyd\'s algorithm (C++)', 'DijkstraFloyd.cc', 'Graph algorithms'],
    ['Fast Dijkstra\'s algorithm (C++)', 'FastDijkstra.cc', 'Graph algorithms'],
    ['Strongly connected components (C)', 'SCC.cc', 'Graph algorithms'],
    #['Kruskal\'s algorithm', 'Kruskal.cpp', 'Graph algorithms'],
    #['Minimum spanning trees (C++)', 'Prim.cc', 'Graph algorithms'],
    ['Eulerian Path (C++)', 'EulerianPath.cc', 'Graph algorithms'],

    ['Suffix arrays (C++)', 'SuffixArray.cc', 'Data structures'],
    ['Binary Indexed Tree', 'BIT.cc', 'Data structures'],
    ['Union-Find Set (C/C++)', 'UnionFind.cc', 'Data structures'],
    ['KD-tree (C++)', 'KDTree.cc', 'Data structures'],
    ['Splay Tree (C++)', 'splay.cpp', 'Data structures'],
    ['Lazy Segment Tree (Java)', 'SegmentTreeLazy.java', 'Data structures'],
    ['Lowest Common Ancestor (C++)', 'LCA.cc', 'Data structures'],

    ['Longest increasing subsequence (C++)', 'LongestIncreasingSubsequence.cc', 'Miscellaneous'],
    #['Topological sort (C++)', 'TopologicalSort.cc', 'Miscellaneous'],
    ['Dates (C++)', 'Dates.cc', 'Miscellaneous'],
    #['Dates (Java)', 'Dates.java', 'Miscellaneous'],
    #['Decimal output formatting (Java)', 'DecFormat.java', 'Miscellaneous'],
    ['Regular expressions (Java)', 'LogLan.java', 'Miscellaneous'],
    ['Prime numbers (C++)', 'Primes.cc', 'Miscellaneous'],
    #['Random STL stuff', 'RandomSTL.cc', 'Miscellaneous'],
    #['Constraint satisfaction problems', 'CSP.cc', 'Miscellaneous'],
    #['Fast exponentiation', 'FastExpo.cpp', 'Miscellaneous'],
    ['C++ input/output', 'IO.cpp', 'Miscellaneous'],
    ['Knuth-Morris-Pratt (C++)', 'KMP.cpp', 'Miscellaneous'],
    ['Latitude/longitude', 'LatLong.cpp', 'Miscellaneous'],
    #['Longest common subsequence', 'LCS.cpp', 'Miscellaneous'],
    #['Miller-Rabin Primality Test (C)', 'MillerRabin.cc', 'Miscellaneous'],
    ['Emacs settings', 'EmacsSettings.txt', 'Miscellaneous'],
    );

sub InsertTOC {
    my ($tmpfile, $tmpfile2) = @_;
    my @contents = `cat $tmpfile`;
    open (FILE, ">$tmpfile2");
    for my $line (@contents){
	chomp $line;
	print FILE $line."\n";
	if ($line eq "<A NAME=\"top\">"){
            print FILE "<CENTER><H1><U>Stanford University ACM Team Notebook (2014-15)</U></H1></CENTER>\n";
	    print FILE "<H1>Table of Contents</H1>\n";
	    for (my $i = 0; $i < @filenames; $i++){
		if ($i == 0 || $filenames[$i][2] ne $filenames[$i-1][2]){
		    if ($i != 0){ print FILE "</OL>\n"; }
		    print FILE "<H2>$filenames[$i][2]</H2>\n\n";
		    print FILE "<OL START=".($i+1).">\n";
		}
		print FILE "<LI><A HREF=\"#file".($i+1)."\">$filenames[$i][0]</A></LI>\n";
	    }
	    print FILE "</OL>\n";
	    print FILE "<HR>\n";
	}
    }
    close FILE;
}

sub Main {
    
    if (@ARGV == 0) {
	print STDERR "Usage: ./format_notebook.pl CODE_DIR [--no_toc]\n";
	exit(1);	
    }

    my $code_dir = "";
    my $toggle_add_toc = 1;
    
    for my $arg (@ARGV) {
	if ($arg eq "--no_toc") {
	    $toggle_add_toc = 0;
	} elsif ($code_dir eq "") {
	    $code_dir = $arg;
	} else {
	    print STDERR "Unexpected argument: $arg\n";
	}
    }

    my $tmpfile = tmpnam();
    my $tmpfile2 = tmpnam();
    
    # preprocess all files
    `g++ -o filter filter.cc`;
    `mkdir filtered`;
    for (my $i = 0; $i < @filenames; $i++) {
	`./filter < $code_dir/$filenames[$i][1] > filtered/$filenames[$i][1]`;
    }    
    
    # initial processing
    my $command = "cd filtered; enscript -G2r -E --color -o $tmpfile --language=html -t \"Stanford University ACM Team Notebook (2013-14)\"";
    for (my $i = 0; $i < @filenames; $i++){ $command .= " ".$filenames[$i][1]; }
    `$command`;

    # add table of contents
    if ($toggle_add_toc) {
	&InsertTOC($tmpfile, $tmpfile2);
	`mv $tmpfile2 $tmpfile`;
    }

    # remove links to top    
    `grep -v '\\[<A HREF="#top">top</A>\\]\\[.*\\]\\[.*\\]' $tmpfile > $tmpfile2`;
    `mv $tmpfile2 $tmpfile`;

    # print final file
    print `cat $tmpfile`;    

    # remove temp files
    `rm $tmpfile`;
    `rm -rf filtered`;
}

&Main;
