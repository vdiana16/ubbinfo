public class NumarComplex {
    private double re;
    private double im;

    //constructori
    public NumarComplex() {}
    public NumarComplex(double re, double im){
        this.re = re;
        this.im = im;
    }

    //getters
    public double getRe() {
        return re;
    }
    public double getIm() {
        return im;
    }

    //setters
    public void setRe(double re) {
        this.re = re;
    }
    public void setIm(double im) {
        this.im = im;
    }

    public NumarComplex conjugat() {
        return new NumarComplex(this.re, -this.im);
    }

    public NumarComplex adunare(NumarComplex z) {
        return new NumarComplex(this.re + z.getRe(), this.im + z.getIm());
    }

    public NumarComplex scadere(NumarComplex z) {
        return new NumarComplex(this.re - z.getRe(), this.im - z.getIm());
    }

    public NumarComplex inmultire(NumarComplex z) {
        double reaux = this.re * z.getRe() - this.im * z.getIm();
        double imaux = this.im * z.getRe() + this.re * z.getIm();
        return new NumarComplex(reaux, imaux);
    }

    public NumarComplex impartire(NumarComplex z) {
        // a+bi/c+di=((a+bi)*(c+di))/((c+di)(c-di))
        NumarComplex deimp = this.inmultire(z.conjugat());
        double imp = z.getRe() * z.getRe() + z.getIm() * z.getIm();
        return new NumarComplex(deimp.getRe()/imp, deimp.getIm()/imp);
    }

    @Override
    public String toString() {
        String rez = new String();
        rez = rez + this.re;
        if (this.im > 0)
        {
            if (this.im == 1)
            {
                rez += "+i";
            }
            else
            {
                rez += "+" + this.im + "*i";
            }
        }
        else if (this.im < 0){
            if (this.im == -1)
            {
                rez += "-i";
            }
            else
            {
                rez += this.im + "*i";
            }
        }
        return rez;
    }
}
