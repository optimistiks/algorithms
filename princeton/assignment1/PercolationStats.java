public class PercolationStats {
    private int times;
    private int size;
    private double[] thresholds;
    
    public PercolationStats(int N, int T) {
        if (N <= 0 || T <= 0) {
            throw new java.lang.IllegalArgumentException();
        }
        
        this.size = N;
        this.times = T;
        this.thresholds = new double[T];
        
        for (int i = 0; i != T; ++i) {
            this.thresholds[i] = this.experiment();
        }
    }
    
    private double experiment() {
        Percolation p = new Percolation(this.size);
        int count = 0;
        
        while (!p.percolates()) {
            int i = StdRandom.uniform(1, this.size + 1);
            int j = StdRandom.uniform(1, this.size + 1);
            p.open(i, j);
            ++count;
        }
        
        return (double) count / (this.size * this.size);
    }
    
    public double mean() {
        return StdStats.mean(this.thresholds);
    }
    
    public double stddev() {
        if (this.times == 1) {
            return Double.NaN;
        }
        
        return StdStats.stddev(this.thresholds);
    }
    
    public double confidenceLo() {
        return this.mean() - ((1.96 * this.stddev()) / Math.sqrt(this.times));
    }
    
    public double confidenceHi() {
        return this.mean() + ((1.96 * this.stddev()) / Math.sqrt(this.times));
    }

    public static void main(String[] args) {
        int N = Integer.parseInt(args[0]);
        int T = Integer.parseInt(args[1]);
        PercolationStats ps = new PercolationStats(N, T);

        String confidence = ps.confidenceLo() + ", " + ps.confidenceHi();
        StdOut.println("mean                    = " + ps.mean());
        StdOut.println("stddev                  = " + ps.stddev());
        StdOut.println("95% confidence interval = " + confidence);
    }
}