public class Percolation {
    private int size;
    private int bottom;
    private boolean[][] sites;
    private WeightedQuickUnionUF uf;
    
    public Percolation(int N) {
        if (N <= 0) {
            throw new java.lang.IllegalArgumentException();
        }
        
        this.size = N;
        this.sites = new boolean[N][N];
        this.uf = new WeightedQuickUnionUF(N * N + 2);
        this.bottom = N * N + 1;
    }
    
    public void open(int i, int j) {
        this.validateIndices(i, j);
        this.sites[i-1][j-1] = true;
        
        //union with virtual top
        if (i == 1) {
            this.uf.union(0, this.xyTo1D(i, j));
        }
        
        //union with virtual bottom
        if (i == this.size) {
            this.uf.union(this.bottom, this.xyTo1D(i, j));
        }
        
        //union with left adjacent open
        if (j > 1 && this.isOpen(i, j - 1)) {
            this.uf.union(this.xyTo1D(i, j), this.xyTo1D(i, j - 1));
        }
        
        //union with right adjacent open
        if (j < this.size && this.isOpen(i, j + 1)) {
            this.uf.union(this.xyTo1D(i, j), this.xyTo1D(i, j + 1));
        }
        
        //union with top adjacent open
        if (i > 1 && this.isOpen(i - 1, j)) {
            this.uf.union(this.xyTo1D(i, j), this.xyTo1D(i - 1, j));
        }
        
        //union with bottom adjacent open
        if (i < this.size && this.isOpen(i + 1, j)) {
            this.uf.union(this.xyTo1D(i, j), this.xyTo1D(i + 1, j));
        }
    }     
    
    public boolean isOpen(int i, int j) {
        this.validateIndices(i, j);
        return this.sites[i-1][j-1];
    }
    
    public boolean isFull(int i, int j) {
        this.validateIndices(i, j);
        return this.uf.connected(0, this.xyTo1D(i, j));
    }
    
    public boolean percolates() {
        return this.uf.connected(0, this.bottom); 
    }
    
    private int xyTo1D(int i, int j) {
        return j * this.size - (this.size - i);
    }
    
    private void validateIndices(int i, int j) {
        if (!(i >= 1 && i <= this.size && j >= 1 && j <= this.size)) {
            throw new java.lang.IndexOutOfBoundsException();
        }
    }

    public static void main(String[] args) {
        Percolation p = new Percolation(6);
        p.open(1, 6);
        StdOut.println(p.isFull(1, 6));
    }
}