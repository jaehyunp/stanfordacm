// Slow but simple Delaunay triangulation.  (from O'Rourke,
// Computational Geometry in C)
//
// Running time: O(n^4)
//
// INPUT:    x[] = x-coordinates
//           y[] = y-coordinates
//
// OUTPUT:   ret[][] = an mx3 matrix containing m triples of indices
//                     corresponding to triangle vertices

import java.util.*;

public class Delaunay {
    int[][] triangulate(double[] x, double[] y) {
	int n = x.length;
	double z[] = new double[n];
	ArrayList<int[]> ret = new ArrayList<int[]>();

	for (int i = 0; i < n; i++)
	    z[i] = x[i] * x[i] + y[i] * y[i];

	for (int i = 0; i < n-2; i++) {
	    for (int j = i+1; j < n; j++) {
		for (int k = i+1; k < n; k++) {
		    if (j == k) continue;
		    double xn = (y[j]-y[i])*(z[k]-z[i]) - (y[k]-y[i])*(z[j]-z[i]);
		    double yn = (x[k]-x[i])*(z[j]-z[i]) - (x[j]-x[i])*(z[k]-z[i]);
		    double zn = (x[j]-x[i])*(y[k]-y[i]) - (x[k]-x[i])*(y[j]-y[i]);
		    boolean flag = zn < 0;
		    for (int m = 0; flag && m < n; m++)
			flag = flag && ((x[m]-x[i])*xn + 
					(y[m]-y[i])*yn + 
					(z[m]-z[i])*zn <= 0);
		    if (flag) ret.add(new int[]{i, j, k});
		}
	    }
	}
	return ret.toArray(new int[0][0]);
    }
}