package domain;

//creeaza, stocheaza si realizeaza operatii cu numere complexe
public class NumarComplex {
    private final double re;
    private final double im;

    public NumarComplex(double re, double im) {
        this.re = re;
        this.im = im;
    }

    //metode
    public NumarComplex adunare(NumarComplex numarComplex) {
        return new NumarComplex(this.re + numarComplex.re, this.im + numarComplex.im);
    }

    public NumarComplex scadere(NumarComplex numarComplex) {
        return new NumarComplex(this.re - numarComplex.re, this.im - numarComplex.im);
    }

    public NumarComplex inmultire(NumarComplex numarComplex) {
        double nRe = this.re * numarComplex.re - this.im * numarComplex.im;
        double nIm = this.re * numarComplex.im + this.im * numarComplex.re;
        return new NumarComplex(nRe, nIm);
    }

    public NumarComplex impartire(NumarComplex numarComplex) {
        double p = numarComplex.re * numarComplex.re + numarComplex.im * numarComplex.im;
        double nRe = (this.re * numarComplex.re + this.im * numarComplex.im) / p;
        double nIm = (this.im * numarComplex.re - this.re * numarComplex.im) / p;
        return new NumarComplex(nRe, nIm);
    }

    @Override
    public String toString() {
        return re + "+" + im + "i";
    }

}
