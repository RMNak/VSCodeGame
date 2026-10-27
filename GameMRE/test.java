// a && b , !(a || b)
interface BoolExpr {}

enum BinaryOps { AND, OR }

class BinaryExpr implements BoolExpr {
    public BoolExpr left;
    public BoolExpr right;
    public BinaryOps op;

    public BinaryExpr(BoolExpr left, BoolExpr right, BinaryOps op) {
        this.left = left;
        this.right = right;
        this.op = op;
    }
}

class NotExpr implements BoolExpr { // ! (expression ) //!a --!!a
    public BoolExpr expr;
    public BinaryOps op;

    public NotExpr(BoolExpr expr) {
        this.expr = expr;
    }
}

class Variable implements BoolExpr {
    public String name;

    public Variable(String name) {
        this.name = name;
    }
}

class Value implements BoolExpr { // true or false
    public boolean value;

    public Value(boolean value) {
        this.value = value;
    }
}

// !(a && b) <==> !a || !b, !(a || b) <==> !a && !b

class Demorganize {
  public BoolExpr demorgan(BoolExpr e) {  
   //!(a && b) ==> !a && !b
   if(e instanceof NotExpr) {
       NotExpr notExpr = (NotExpr) e;
       if(notExpr.expr instanceof BinaryExpr) {
           BinaryExpr binaryExpr = (BinaryExpr) notExpr.expr;
           if(binaryExpr.op == BinaryOps.AND) {
               return new BinaryExpr(new NotExpr(binaryExpr.left), new NotExpr(binaryExpr.right), BinaryOps.OR);
           } else if(binaryExpr.op == BinaryOps.OR) {
               return new BinaryExpr(new NotExpr(binaryExpr.left), new NotExpr(binaryExpr.right), BinaryOps.AND);
           }
       }
    }    
  }
}

