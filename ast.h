/**************************************
 *
 * University of Haifa
 *
 * Theory of compilation
 *
 * P machine compiler - code generation project
 *
 * Yosi Ben Asher
 * Email: yosibenasher@gmail.com
 *
 * Mariah Akree
 * Email: mariah.uni.haifa@gmail.com
 *
 **************************************/
 /*   PROGRAM = 258,
      BBEGIN = 259,
      END = 260,
      DECLARE = 261,
      PROCEDURE = 262,
      FUNCTION = 263,
      LABEL = 264,
      INTEGER = 265,
      REAL = 266,
      RECORD = 267,
      BOOLEAN = 268,
      ARRAY = 269,
      OF = 270,
      ASSIGN = 271,
      LC = 272,
      RC = 273,
      IF = 274,
      THEN = 275,
      ELSE = 276,
      WHILE = 277,
      REPEAT = 278,
      FI = 279,
      DO = 280,
      OD = 281,
      READ = 282,
      WRITE = 283,
      TRUE = 284,
      FALSE = 285,
      ADD = 286,
      MIN = 287,
      MUL = 288,
      DIV = 289,
      GOTO = 290,
      MOD = 291,
      LES = 292,
      LEQ = 293,
      EQU = 294,
      NEQ = 295,
      GRE = 296,
      GEQ = 297,
      AND = 298,
      OR = 299,
      NOT = 300,
      CASE = 301,
      FOR = 302,
      FIN = 303,
      IDENTICAL = 304,
      FROM = 305,
      BY = 306,
      TO = 307,
      NEW = 308,
      INTCONST = 309,
      IDE = 310,
      REALCONST = 311,
      STRING = 312,
      DUMMY = 313*/

#ifndef AST_H 
#define AST_H

#include <iostream>
#include <assert.h>
#include <string>
#include <map>
#include <vector>
#include <list>

using namespace std;
enum VariableType { Simple, Idle, Address, Record, Array };
enum DataType {SymbolTableData,AddressData,RecordData,ArrayData, SimpleData ,RecordChildrenData ,MixedData, NoneData };
enum Status{ OFF, ON };
enum CaseType{ NONE , Declare , State};
enum OperationType {Function, Procedure, Neither};

struct SymbolTableDetails {
    int Address;
    int Size;
    VariableType Type;
    int Operation = Neither;
    int relativefunction;
};
struct Dimension{
    int Lower_Bound = 0;
    int Upper_Bound = 0;
};

struct ArrayDetails {
    int Address_;
    string name;
    VariableType Type;
    int SizeOfArray;
    int Subpart = 0;
    vector<Dimension> Dimensions;
    vector<int> IXA_List;
    DataType DataType_;
};
struct AddressDetails{
    int Address_;
    string name;
    int size = 1;
    string PointsTo;
    int PointsToAddress;
    VariableType Type = Address;
    DataType Datatype_;
};
struct RecordDetails {
    int Address;
    string name;
    int ParameterCounters;
    int size = 0;
    DataType DataType_;
};
struct RecordChild {
    string name;
    int Address;
    int size;
    int offset;
    int rootIndex;
    int InnerParamterCounter = 0;
    DataType DataTye_;
    VariableType type;
    int PointsToAddress = 0;
    string PointsToName = "";
};
struct Operation{
    string name = "";
    int ParametersCounter = 0;
    int Dynamic_Link = 0;
    int Static_Link = 0;
    OperationType Type = Neither;
    Operation* Sibling ;
};
struct OperationParameter{
    int Address; //or offset that is needed for LDA opcode
    string Name;
    int Size;
    VariableType Type;
    int OperationRootIndex = 0;
    string OperationName;
    
};

/**
 * classes
 */
 // base class for tree nodes
 //Data Base! - SymbolTable
extern map<string, SymbolTableDetails> SymbolTable;

static vector<ArrayDetails> ArrayList;
static vector<Dimension> ArrayInnerDimensions;
static vector<AddressDetails> AddressList;
static vector<RecordDetails> RecordsList;
static vector<RecordChild> RecordChildren;
static vector<Operation> OperationList;
static vector<OperationParameter> OperationParametersList;

//Counters
static int ParameterCounter = 0;
static int CurrentAddress = 5;
static int IfCounter = 0;
static int ElseCounter = 0;
static int Loop_Counter = 0;
static int CurrentCase = 1;
static int Cases_Counter = 1;
static int Cases_MaxCounter = 0;
static int Max_LOOP = 0;
static int Max_If = 0;

//Flags
static int Add_Flag = 0;
static int Sub_Flag = 0;
static int Inc_Flag = 0;
static int Dec_Flag = 0;
static int Const_Detector = 0;

static int Ind_Flag = 0;

//Values
static int IF_MaxCounter = 0;

//Assignment2
//CreatedObject is Parameter Save name of Object that being created...
static string CreatedObject = "";
static string ObjectNotCreated = "";
static VariableType DetectorOfVariable;
static CaseType Condition = NONE;
//====================================================================
//Counters of all types
static int RecordsCounter = 0;
static int AddressesCounter = 0;
static int SimplesCounter = 0;
static int ArraysCounter = 0;
//====================================================================
//Detectors --------------------- NOT USED ---------------------------
//Current Variable Declaration is Simple!
/*static int IsSimple = OFF;
//Current Variable Declaration is Address!
static int IsAddress = OFF;
//Current Variable Declaration is Array!
static int IsArray = OFF;
//Current Variable Declaration is Record!
static int IsRecord = OFF;*/
//Object Inside Object Detector ...
static int IsInsideRecord = OFF;
static int IsInsideArray = OFF;
//====================================================================
//Record Features
//Record Current Index for Declaration
static int RecordIndex = -1;
//Record Current Size for Declaration
static int RecordSize = 0;
//Record SAVE Name
static string RecordName = "";
//Parameters Inside Record
static int RecordParametersCounter = 0;
//====================================================================
//Array Features
//Array SAVE Name
static string ArrayName = "";
//Array Current Index for Declaration
static int ArrayIndex = -1;
//Array Current Size for Declaration
static int ArraySize = 0;
//Array Subpart Value for Declaration
static int ArraySubpart = 0;
//Array Single Object Size for Declaration
static int SizeOfSingleObject = 1;
static int ArrayDimIndex = 0;
//Array Type Detector = 1;
static string ArrayTypeDetector = "";
//Array Current Dimensions for Declaration
//====================================================================
//Address Features
//Address Current Name used to store name of IdeType
static string AddressName = "";
//Address Current Address used to store address of IdeType
static int PointsToAddress = -1;
//Address PointsTo String
static string PointsTo = "";
//Special Cases!!
//Record Inside Record
/*static int RecordInRecord = OFF;
//Array Inside Array
static int ArrayInArray = OFF;*/
static int ArrayDimReceiver = 0;
/*
static void PrintDataType(DataType input,ostream& os)
{
    switch (input)
    {
        case SymbolTableData:
            os << "SymbolTable Data" << endl;
            break;
        case AddressData:
            os << "Address Data" << endl;
            break;
        case ArrayData:
            os << "Array Data" << endl;
            break;
        case RecordData:
            os << "Record Data" << endl;
            break;
        case RecordChildrenData:
            os << "Record Children Data" << endl;
            break;
        case MixedData:
            os << "Mixed Data (Record)" << endl;
            break;
        default:
            os << "None Data " << endl;
            break;

    }
}
*/
/*
DataType GetDataType(int input)
{
    switch (input) {
        case Simple: return SimpleData; break;
        case Array: return ArrayData; break;
        case Record: return RecordData; break;
        case Idle: return RecordChildrenData; break;
        case Address: return AddressData; break;
        default: return NoneData;
    }
}
*/

/*static std::vector<int> reverseVector(std::vector<int> v) {
    // create an empty vector to store the reversed elements
    std::vector<int> reversed;

    // iterate through the original vector in reverse order and add each element to the reversed vector
    for (int i = v.size() - 1; i >= 0; i--) {
        reversed.push_back(v[i]);
    }

    // return the reversed vector
    return reversed;
}*/

//====================================================================

//Assignment 3
static string ProgramName = "";
static int Static_Link = 0;
static string currentFuncOrProcName = "";
static int relativeAddress = 5;

//Operation Features
static string OperationName = "";
static int OperationIndex = -1;
static int OperationParameterCounter = 0;
static OperationType OperationType_ = Neither;

//Counters For Assignment 3
static int paramterlistcounter = 5;

class Object {
public:
    virtual void print(ostream& os) = 0;
    virtual void pcodegen(ostream& os) = 0;
    virtual Object* clone() const { return NULL; }
    virtual ~Object() {}
};

class Expr : public Object {
public:
    // Unary operations
    Expr(int op, Object* atom) : op_(op), atom_(atom), left_(NULL), right_(NULL), unary_(true) {}
    // Binary operations
    Expr(int op, Object* left, Object* right) : op_(op), left_(left), right_(right), atom_(NULL), unary_(false) {}

    Expr(const Expr& exp) {
        unary_ = exp.unary_;
        op_ = exp.op_;
        left_ = exp.left_->clone();
        right_ = exp.right_->clone();
        atom_ = exp.atom_->clone();
    }
    virtual ~Expr() {
        if (left_) delete left_;
        if (right_) delete right_;
        if (atom_) delete atom_;
    }
    void print(ostream& os) {
        os << "Node name : Expr" << endl;
        assert(op_);
        if (unary_) {
            os << "Unary op is : " << op_;
            assert(atom_);
            atom_->print(os);
        }
        else {
            os << "Binary op is : " << op_;
            assert(left_ && right_);
            left_->print(os);
            right_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        if (op_ == 271 || op_ == 292 || op_ == 293 || op_ == 294 || op_ == 295 || op_ == 296 || op_ == 297)
        {
            Ind_Flag = 1;
        }
        if (unary_ == false)
        {
            int Temp_ConstDetect = Const_Detector;

            assert(left_ && right_);
            right_->pcodegen(os);
            Const_Detector = 0;
            // = (op_ == 286 || op_ == 287), Dec_Flag = (op_ == 286 || op_ == 287);
            Add_Flag = (op_ == 286), Sub_Flag = (op_ == 287);
            int unimportant1 = Ind_Flag;
            left_->pcodegen(os);

            switch (op_)
            {

            case 286:
                /*Add_Flag = 1;
                Sub_Flag = 0;*/
                if (Add_Flag & !Const_Detector)
                {
                    os << "add" << endl;
                }
                break;
            case 287:
                /*Add_Flag = 0;
                Sub_Flag = 1;*/
                if (Sub_Flag & !Const_Detector)
                {
                    os << "sub" << endl;
                }
                break;
            case 288:
                os << "mul" << endl;
                break;

            case 289:
                os << "div" << endl;
                break;

            case 290:
                os << "goto" << endl;
                break;

            case 291:
                os << "mod" << endl;
                break;

            case 292:
                os << "les" << endl;
                break;

            case 293:
                os << "leq" << endl;
                break;

            case 294:
                os << "equ" << endl;
                break;

            case 295:
                os << "neq" << endl;
                break;

            case 296:
                os << "grt" << endl;
                break;

            case 297:
                os << "geq" << endl;
                break;

            case 298:
                os << "and" << endl;
                break;

            case 299:
                os << "or" << endl;
                break;
            default:
                break;
            }

            Const_Detector = Temp_ConstDetect;
            Ind_Flag = unimportant1;
            Add_Flag = 0;
            Sub_Flag = 0;
        }
        if (unary_ == true)
        {
            int temp = Ind_Flag;
            assert(atom_);
            atom_->pcodegen(os);
            switch (op_)
            {
            case 287:
                os << "neg" << endl;
                break;
            case 300:
                os << "not" << endl;
                break;
            default:
                break;
            }
            Ind_Flag = temp;
        }
    }
    virtual Object* clone() const { return new Expr(*this); }

private:
    bool unary_;
    int op_;
    Object* left_;
    Object* right_;
    Object* atom_;
};

class ExprList : public Object {
public:
    ExprList(Object* expr) : expr_(expr), expr_list_(NULL) { assert(expr_); }
    ExprList(Object* expr, Object* expr_list) : expr_(expr), expr_list_(expr_list) { assert(expr_ && expr_list_); }

    ExprList(const ExprList& exp) {
        expr_ = exp.expr_->clone();
        expr_list_ = exp.expr_list_->clone();
    }

    virtual ~ExprList() {
        if (expr_) delete expr_;
        if (expr_list_) delete expr_list_;
    }

    void print(ostream& os) {
        os << "Node name : ExprList";
        assert(expr_);
        expr_->print(os);
        if (expr_list_) {
            expr_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(expr_);
        expr_->pcodegen(os);
        if (expr_list_) {
            expr_list_->pcodegen(os);
        }
    }
    virtual Object* clone() const { return new ExprList(*this); }

private:
    Object* expr_;
    Object* expr_list_;
};

class Dim : public Object {
public:
    Dim(Object* exp) : exp_(exp), dim_(NULL) { assert(exp_); }
    Dim(Object* exp, Object* dim) : exp_(exp), dim_(dim) { assert(exp_ && dim_); }

    Dim(const Dim& d) {
        exp_ = d.exp_->clone();
        dim_ = d.dim_->clone();
    }

    virtual ~Dim() {
        if (exp_) delete exp_;
        if (dim_) delete dim_;
    }

    void print(ostream& os) {
        os << "Node name : Dim" << endl;
        assert(exp_);
        exp_->print(os);
        if (dim_) {
            dim_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(exp_);

        exp_->pcodegen(os);
        os << "ixa " << ArrayList[ArrayIndex].IXA_List.back() << endl;
        ArrayList[ArrayIndex].IXA_List.pop_back();

        if (dim_) {
            ArrayDimIndex++;
            dim_->pcodegen(os);

        }
   }
    virtual Object* clone() const { return new Dim(*this); }

private:
    Object* exp_;
    Object* dim_;
};

class Atom : public Object {
};

class IntConst : public Atom {
public:
    IntConst(const int i) : i_(i) {}
    IntConst(const IntConst& in) : i_(in.i_) {}

    void print(ostream& os) {
        os << "Node name : IntConst. Value is :" << i_ << endl;
    }
    void pcodegen(ostream& os) {
        if(DetectorOfVariable == Array)
        {
            ArrayDimReceiver = i_;
        }
        Const_Detector = 1;
        Inc_Flag = 1, Dec_Flag = 1;
        if (Add_Flag && Inc_Flag)
        {
            os << "inc " << i_ << endl;
            Inc_Flag = 0, Dec_Flag = 0;
        }
        else if (Sub_Flag && Dec_Flag)
        {
            os << "dec " << i_ << endl;
            Inc_Flag = 0, Dec_Flag = 0;
        }
        else
        {
            Const_Detector = 0;
            os << "ldc " << i_ << endl;
        }

    }
    virtual Object* clone() const { return new IntConst(*this); }

private:
    const int i_;
};

class RealConst : public Atom {
public:
    RealConst(const double r) : r_(r) {}
    RealConst(const RealConst& in) : r_(in.r_) {}

    void print(ostream& os) {
        os << "Node name : RealConst. Value is :" << r_ << endl;
    }
    void pcodegen(ostream& os) {
        Const_Detector = 1;
        Inc_Flag = 1, Dec_Flag = 1;
        if (Add_Flag && Inc_Flag)
        {
            os << "inc " << r_ << endl;
            Inc_Flag = 0, Dec_Flag = 0;
        }
        else if (Sub_Flag && Dec_Flag)
        {
            os << "dec " << r_ << endl;
            Inc_Flag = 0, Dec_Flag = 0;
        }
        else
        {
            Const_Detector = 0;
            os << "ldc " << r_ << endl;
        }
    }

    virtual Object* clone() const { return new RealConst(*this); }

private:
    const double r_;
};

class True : public Atom {
public:
    void print(ostream& os) {
        os << "Node name : trueConst. Value is true" << endl;
    }
    void pcodegen(ostream& os) {
        os << "ldc" << 1 << endl;
    }
    virtual Object* clone() const { return new True(); }

};

class False : public Atom {
public:
    void print(ostream& os) {
        os << "Node name : trueConst. Value is false" << endl;
    }
    void pcodegen(ostream& os) {
        os << "ldc" << 0 << endl;
    }
    virtual Object* clone() const { return new False(); }
};

class Var : public Atom {
};

class ArrayRef : public Var {
public:
    ArrayRef(Object* var, Object* dim) : var_(var), dim_(dim) { assert(var_ && dim_); }
    ArrayRef(const ArrayRef& arr) {
        var_ = arr.var_->clone();
        dim_ = arr.dim_->clone();
    }

    virtual ~ArrayRef() {
        if (var_) delete var_;
        if (dim_) delete dim_;
    }

    void print(ostream& os) {
        os << "Node name : ArrayRef" << endl;
        assert(var_ && dim_);
        var_->print(os);
        dim_->print(os);
    }
    void pcodegen(ostream& os) {
        DetectorOfVariable = Array;
        assert(var_ && dim_);
        vector<int> temp = ArrayList[ArrayIndex].IXA_List;
        var_->pcodegen(os);
        dim_->pcodegen(os);
        os << "dec " << ArraySubpart << endl;
        ArrayList[ArrayIndex].IXA_List = temp;
    }
    virtual Object* clone() const { return new ArrayRef(*this); }

private:
    Object* var_;
    Object* dim_;
};

class RecordRef : public Var {
public:
    RecordRef(Object* varExt, Object* varIn) : varExt_(varExt), varIn_(varIn) { assert(varExt_ && varIn_); }
    RecordRef(const RecordRef& rec) {
        varExt_ = rec.varExt_->clone();
        varIn_ = rec.varIn_->clone();
    }

    virtual ~RecordRef() {
        if (varExt_) delete varExt_;
        if (varIn_) delete varIn_;
    }

    void print(ostream& os) {
        os << "Node name : RecordRef" << endl;
        assert(varExt_ && varIn_);
        varExt_->print(os);
        varIn_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(varExt_ && varIn_);
       // VariableType Previous = DetectorOfVariable;
        DetectorOfVariable = Record;
       // IsInsideRecord = ON;
        varExt_->pcodegen(os);
        //IsInsideRecord = OFF;
        //DetectorOfVariable = Previous;

        IsInsideRecord = ON;
        varIn_->pcodegen(os);
        IsInsideRecord = OFF;


    }
    virtual Object* clone() const { return new  RecordRef(*this); }

private:
    Object* varExt_;
    Object* varIn_;
};

class AddressRef : public Var {
public:
    AddressRef(Object* var) : var_(var) { assert(var_); }
    AddressRef(const AddressRef& addre) {
        var_ = addre.var_->clone();
    }

    virtual ~AddressRef() {
        if (var_) delete var_;
    }

    void print(ostream& os) {
        os << "Node name : AddressRef" << endl;
        assert(var_);
        var_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_);
        DetectorOfVariable = Address;
        var_->pcodegen(os);
        os << "ind" << endl;
    }
    virtual Object* clone() { return new AddressRef(*this); }

private:
    Object* var_;
};

class Statement : public Object {
};

class NewStatement : public Statement {
public:
    NewStatement(Object* var) : var_(var) { assert(var_); }
    NewStatement(const NewStatement& ns) {
        var_ = ns.var_->clone();
    }

    virtual ~NewStatement() {
        if (var_) delete var_;
    }

    void print(ostream& os) {
        os << "Node name : NewStatement";
        assert(var_);
        var_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_);

        var_->pcodegen(os);
        os << "ldc " << RecordSize << endl;
        os << "new " << endl;


    }
    virtual Object* clone() { return new NewStatement(*this); }

private:
    Object* var_;
};

class WriteStrStatement : public Statement {
public:
    WriteStrStatement(const char* str) {
        str_ = new string(str);
    }

    WriteStrStatement(const WriteStrStatement& ns) {
        str_ = new string(*ns.str_);
    }

    virtual ~WriteStrStatement() {
        if (str_) delete str_;
    }
    void print(ostream& os) {
        os << "Node name : WriteStrStatement";
        assert(str_);
        os << "Str statement is: " << str_ << endl;
    }
    void pcodegen(ostream& os) {
        assert(str_);
        os << "print" << endl;

    }
    virtual Object* clone() { return new WriteStrStatement(*this); }

private:
    string* str_;
};

class WriteVarStatement : public Statement {
public:
    WriteVarStatement(Object* exp) : exp_(exp) { assert(exp_); }

    WriteVarStatement(const WriteVarStatement& ex) {
        exp_ = ex.clone();
    }

    virtual ~WriteVarStatement() {
        if (exp_) delete exp_;
    }

    void print(ostream& os) {
        os << "Node name : WriteVarStatement";
        assert(exp_);
        exp_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(exp_);
        int Temporary_Ind = Ind_Flag;
        Ind_Flag = 1;
        exp_->pcodegen(os);
        Ind_Flag = Temporary_Ind;
        os << "print" << endl;
    }
    virtual Object* clone() const { return new WriteVarStatement(*this); }

private:
    Object* exp_;
};

class ProcedureStatement : public Statement {
public:
    ProcedureStatement(const char* str) {
        str_ = new string(str);
    }

    ProcedureStatement(Object* expr_list, const char* str) : expr_list_(expr_list) {
        assert(expr_list_);
        str_ = new string(str);
    }

    ProcedureStatement(const ProcedureStatement& ps) {
        expr_list_ = ps.expr_list_->clone();
        str_ = new string(*ps.str_);
    }

    virtual ~ProcedureStatement() {
        if (str_) delete str_;
        if (expr_list_) delete expr_list_;
    }

    void print(ostream& os) {
        os << "Node name : ProcedureStatement. Proc name : " << *str_ << endl;
        if (expr_list_) {
            expr_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        int index =0;
        bool IsFound = false;
        for(auto var : OperationList)
        {
            if(var.name == *str_ && IsFound == false)
            {
                IsFound = true;
            }
            if(IsFound == false)
            {
                index++;
            }

        }
        os << "mst " << index << endl;

        if (expr_list_) {
            expr_list_->pcodegen(os);
        }
        os << "cup " << OperationList.at(index).ParametersCounter << " " << OperationList.at(index).name << endl;

    }
    virtual Object* clone() const { return new ProcedureStatement(*this); }

private:
    Object* expr_list_;
    string* str_;
};

class Case : public Object {
public:
    Case(Object* stat_list, int val) : leafChild_(NULL), stat_list_(stat_list) {
        // note the special treatment in miny.y for this case (makenode)
        leafChild_ = new IntConst(val);
        assert(stat_list_);
    }

    Case(const Case& c) {
        stat_list_ = c.stat_list_->clone();
        leafChild_ = c.leafChild_->clone();
    }

    virtual ~Case() {
        if (stat_list_) delete stat_list_;
        if (leafChild_) delete leafChild_;
    }

    void print(ostream& os) {
        os << "Node name : Case";
        assert(stat_list_);
        stat_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(stat_list_);
        stat_list_->pcodegen(os);

    }
    virtual Object* clone() const { return new Case(*this); }

private:
    Object* stat_list_;
    Object* leafChild_;
};

class CaseList : public Object {
public:
    CaseList(Object* ccase) : case_(ccase), case_list_(NULL) { assert(case_); }
    CaseList(Object* ccase, Object* case_list) : case_(ccase), case_list_(case_list) { assert(case_ && case_list_); }

    CaseList(const CaseList& cl) {
        case_ = cl.case_->clone();
        case_list_ = cl.case_list_->clone();
    }

    virtual ~CaseList() {
        if (case_) delete case_;
        if (case_list_) delete case_list_;
    }

    void print(ostream& os) {
        os << "Node name : CaseList";
        assert(case_);
        case_->print(os);
        if (case_list_) {
            case_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(case_);
        int CurrentCase_Counter = CurrentCase++;
        os << "case_" << CurrentCase_Counter << "_" << Cases_MaxCounter << ":" << endl;
        case_->pcodegen(os);
        os << "ujp end_switch_" << Cases_MaxCounter << endl;
        if (case_list_) {
            case_list_->pcodegen(os);
        }
        os << "ujp case_" << CurrentCase_Counter << "_" << Cases_MaxCounter << endl;

    }
    virtual Object* clone() const { return new CaseList(*this); }

private:
    Object* case_;
    Object* case_list_;
};

class CaseStatement : public Statement {
public:
    CaseStatement(Object* exp, Object* case_list) : exp_(exp), case_list_(case_list) { assert(exp_ && case_list_); }

    CaseStatement(const CaseStatement& cs) {
        exp_ = cs.exp_->clone();
        case_list_ = cs.case_list_->clone();
    }

    virtual ~CaseStatement() {
        if (exp_) delete exp_;
        if (case_list_) delete case_list_;
    }

    void print(ostream& os) {
        os << "Node name : CaseStatement";
        assert(exp_ && case_list_);
        exp_->print(os);
        case_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(exp_ && case_list_);
        int Temporary_CurrentCase = CurrentCase;
        int Temporary_CaseCounter = Cases_MaxCounter;
        int Temporary_IndFlag = Ind_Flag;
        Cases_MaxCounter = Cases_Counter++;
        CurrentCase = 1;
        Ind_Flag = 1;
        exp_->pcodegen(os);
        os << "neg" << endl;
        Ind_Flag = Temporary_IndFlag;
        os << "ixj end_switch_" << Cases_MaxCounter << endl;
        case_list_->pcodegen(os);
        os << "end_switch_" << Cases_MaxCounter << ":" << endl;
        Cases_MaxCounter = Temporary_CaseCounter;
        CurrentCase = Temporary_CurrentCase;
    }
    virtual Object* clone() const { return new CaseStatement(*this); }

private:
    Object* exp_;
    Object* case_list_;
};

class LoopStatement : public Statement {
public:
    LoopStatement(Object* exp, Object* stat_list) : exp_(exp), stat_list_(stat_list)
    {
        assert(exp_ && stat_list_);
    }

    LoopStatement(const LoopStatement& ls) {
        exp_ = ls.exp_->clone();
        stat_list_ = ls.stat_list_->clone();
    }

    virtual ~LoopStatement() {
        if (exp_) delete exp_;
        if (stat_list_) delete stat_list_;
    }

    void print(ostream& os) {
        os << "Node name : LoopStatement";
        assert(exp_ && stat_list_);
        exp_->print(os);
        stat_list_->print(os);
    }
    void pcodegen(ostream& os) {

        Loop_Counter++;
        Max_LOOP = Loop_Counter;
        int save_counter;
        assert(exp_ && stat_list_);
        os << "loop_" << Loop_Counter << ":" << endl;
        int Temporary_IndFlag = Ind_Flag;
        Ind_Flag = 1;
        exp_->pcodegen(os);
        Ind_Flag = Temporary_IndFlag;
        os << "fjp" << " end_loop_" << Loop_Counter << endl;

        save_counter = Loop_Counter;
        stat_list_->pcodegen(os);
        Loop_Counter = save_counter;

        os << "ujp" << " loop_" << Loop_Counter << endl;
        os << "end_loop_" << Loop_Counter << ":" << endl;
        Loop_Counter = Max_LOOP;

    }
    virtual Object* clone() const { return new LoopStatement(*this); }

private:
    Object* exp_;
    Object* stat_list_;
};

class ConditionalStatement : public Statement {
public:
    ConditionalStatement(Object* exp, Object* stat_list_if) : exp_(exp), stat_list_if_(stat_list_if), stat_list_else_(NULL)
    {
        assert(exp_ && stat_list_if_);
        if (stat_list_if)

        {
        }     // IfCounter++;
        if (stat_list_else_) {}
        // ElseCounter++;
    }
    ConditionalStatement(Object* exp, Object* stat_list_if, Object* stat_list_else) : exp_(exp), stat_list_if_(stat_list_if), stat_list_else_(stat_list_else)
    {
        assert(exp_ && stat_list_if_ && stat_list_else_);
        if (stat_list_if) {}
        //   IfCounter++;
        if (stat_list_else_) {}
        //   ElseCounter++;
    }

    ConditionalStatement(const ConditionalStatement& cs) {
        exp_ = cs.exp_->clone();
        stat_list_if_ = cs.stat_list_if_->clone();
        stat_list_else_ = cs.stat_list_else_->clone();
        if (stat_list_if_)
            IfCounter++;
        if (stat_list_else_)
            ElseCounter++;
    }

    virtual ~ConditionalStatement() {
        if (exp_) delete exp_;
        if (stat_list_if_)
        {
            delete stat_list_if_;
        }
        if (stat_list_else_)
        {
            delete stat_list_else_;
        }
    }

    void print(ostream& os) {
        os << "Node name : ConditionalStatement";
        assert(exp_ && stat_list_if_);
        exp_->print(os);
        stat_list_if_->print(os);
        if (stat_list_else_) {
            stat_list_else_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        // os << "here " << IfCounter << endl;
        assert(exp_ && stat_list_if_);
        IF_MaxCounter++;
        IfCounter = IF_MaxCounter;
        Max_If = IfCounter;
        int save_counter_if = 0;
        int temp = Ind_Flag;
        Ind_Flag = 1;
        exp_->pcodegen(os);
        Ind_Flag = temp;
        if (stat_list_else_)
        {
            os << "fjp end_else_" << IfCounter << endl;
        }
        else
        {
            os << "fjp end_if_" << IfCounter << endl;
        }

        int temp_exp = Ind_Flag;
        Ind_Flag = 1;

        save_counter_if = IfCounter;
        stat_list_if_->pcodegen(os);
        IfCounter = save_counter_if;


        Ind_Flag = temp_exp;


        if (stat_list_else_) {
            int temp_exp = Ind_Flag;
            Ind_Flag = 1;

            os << "ujp end_if" << IfCounter << endl;
            os << "else_if_" << IfCounter << ":" << endl;

            save_counter_if = IfCounter;
            stat_list_else_->pcodegen(os);
            IfCounter = save_counter_if;

            Ind_Flag = temp_exp;
        }

        os << "end_if_" << IfCounter << ": " << endl;
        IfCounter = Max_If;

    }
    virtual Object* clone() const { return new ConditionalStatement(*this); }

private:
    Object* exp_;
    Object* stat_list_if_;
    Object* stat_list_else_;
};

class Assign : public Statement {
public:
    Assign(Object* var, Object* exp) : var_(var), exp_(exp) { assert(var_ && exp_); }

    Assign(const Assign& as) {
        var_ = as.var_->clone();
        exp_ = as.exp_->clone();
    }

    virtual ~Assign() {
        if (exp_) delete exp_;
        if (var_) delete var_;
    }

    void print(ostream& os) {
        os << "Node name : Assign";
        assert(var_ && exp_);
        exp_->print(os);
        var_->print(os);

    }
    void pcodegen(ostream& os)
    {/*

        {
            os << "========= Symbol Table ==========" << endl;
            int current = 0;
            for (const auto& var : SymbolTable)
            {
                os << "Object :" << current << "| Name :" << var.first << "| Address :" << var.second.Address << "| Size :" << var.second.Size << "| Type :" << var.second.Type << endl;
                current++;
            }
            os << "========= Children Of Records ==========" << endl;
            current = 0;
            for (auto var : RecordChildren)
            {
                os << "Object :" << current << "| Name :" << var.name << "| Address :" << var.Address << "| Size :" << var.size << "| Type :" << var.type << "| Offset: " << var.offset << "| Root :" << var.rootIndex << endl;
                current++;
            }
            os << "========= Records List ==========" << endl;
            current = 0;
            for (auto var : RecordsList)
            {
                os << "Object :" << current << "| Name :" << var.name << "| Address :" << var.Address << "| Size :" << var.size << "| Parameter Count :" << var.ParameterCounters << "| DataType :" << var.DataType_<< endl;
                current++;
            }
            os << "========= Array List ==========" << endl;
            current = 0;
            for(auto var : ArrayList)
            {
                os << "Object :" << current <<" name :" << var.name << " address :" << var.Address_ << " Size :" << var.SizeOfArray << " DataType :" << var.DataType_ << endl;
                current++;
            }

            os << "========= List Address ==========" << endl;
            current = 0;
            for(auto var : AddressList)
            {
                os << "Object :" << current <<" name :" << var.name << " address :" << var.Address_ << " Size :" << var.size << " PointsTo(string) :" << var.PointsTo << " PointsToAddress :" << var.PointsToAddress << endl;
                current++;
            }

            os << "Counters OF ALL:" << endl;
            os << "Simples = " << SimplesCounter << "| Arrays = " << ArraysCounter << " |Addresses = " << AddressesCounter << " |Records = " << RecordsCounter << endl;

        }*/

        assert(var_ && exp_);
        int temp_ = Ind_Flag;
        Ind_Flag = 0;
        exp_->pcodegen(os);
        Ind_Flag = 1;
        var_->pcodegen(os);

        Ind_Flag = temp_;
        os << "sto" << endl;
        // Sto_Flag = 0;


    }
    virtual Object* clone() const
    {
        return new Assign(*this);
    }

private:
    Object* var_;
    Object* exp_;
};

class StatementList : public Object {
public:
    StatementList(Object* stat) : stat_list_(NULL), stat_(stat) { assert(stat_); }
    StatementList(Object* stat_list, Object* stat) : stat_list_(stat_list), stat_(stat) { assert(stat_list_ && stat); }

    StatementList(const StatementList& sl) {
        stat_ = sl.stat_->clone();
        stat_list_ = sl.stat_list_->clone();
    }

    virtual ~StatementList() {
        if (stat_) delete stat_;
        if (stat_list_) delete stat_list_;
    }

    void print(ostream& os) {
        os << "Node name : StatementList" << endl;
        if (stat_list_) {
            stat_list_->print(os);
        }
        assert(stat_);
        stat_->print(os);
    }
    void pcodegen(ostream& os) {
        Condition = State;
        if (stat_list_) {
            Condition = State;
            stat_list_->pcodegen(os);
            Condition = NONE;
        }
        assert(stat_);
        Condition = State;
        stat_->pcodegen(os);
        Condition = NONE;
    }
    virtual Object* clone() const { return new StatementList(*this); }

private:
    Object* stat_;
    Object* stat_list_;
};

class RecordList : public Object {
public:
    RecordList(Object* var_decl) : record_list_(NULL), var_decl_(var_decl) { assert(var_decl_); }
    RecordList(Object* record_list, Object* var_decl) : record_list_(record_list), var_decl_(var_decl) { assert(record_list_ && var_decl); }

    RecordList(const RecordList& li) {
        var_decl_ = li.var_decl_->clone();
        record_list_ = li.record_list_->clone();
    }

    virtual ~RecordList() {
        if (var_decl_) delete var_decl_;
        if (record_list_) delete record_list_;
    }

    void print(ostream& os) {
        os << "Node name : RecordList" << endl;
        if (record_list_) {
            record_list_->print(os);
        }
        assert(var_decl_);
        var_decl_->print(os);
    }
    void pcodegen(ostream& os) {
        //VariableType SAVE;
        if (record_list_) {
            IsInsideRecord = ON;
            DetectorOfVariable = Record;
            record_list_->pcodegen(os);
            IsInsideRecord = OFF;
        }
        assert(var_decl_);
        IsInsideRecord = ON;
        var_decl_->pcodegen(os);
        IsInsideRecord = OFF;
        DetectorOfVariable = Record;

    }
    virtual Object* clone() const { return new RecordList(*this); }

private:
    Object* var_decl_;
    Object* record_list_;
};

class Type : public Object {
};

class SimpleType : public Type {
public:
    SimpleType(const char* name) {
        name_ = new string(name);
    }

    virtual ~SimpleType() {
        if (name_)delete name_;
    }

    SimpleType(const SimpleType& s) {
        name_ = new string(*s.name_);
    }

    void print(ostream& os) {
        os << "Node name : SimpleType" << endl;;
        os << "Type is : " << (*name_) << endl;
    }
    void pcodegen(ostream& os) {
         SimplesCounter++;
         DetectorOfVariable = Simple;
         if(IsInsideArray == ON)
         ArrayTypeDetector = *name_;
    }
    virtual Object* clone() const { return new SimpleType(*this); }

private:
    string* name_;
};

class IdeType : public Type {
public:
    IdeType(const char* name) {
        name_ = new string(name);
    }

    virtual ~IdeType() {
        if (name_) delete name_;
    }

    IdeType(const IdeType& s) {
        name_ = new string(*s.name_);
    }

    void print(ostream& os) {
        os << "Node name : IdeType" << endl;
    }
    void pcodegen(ostream& os) {
        if(Condition == Declare)
        {
            if(IsInsideRecord == ON)
            {
                PointsTo = *name_;
                bool Is_It_Found = false;
                //SymbolTable
                if (Is_It_Found == false)
                    for (auto var: SymbolTable) {
                        if (var.first == PointsTo) {
                            Is_It_Found = true;
                            PointsToAddress = var.second.Address;
                        }
                    }
                //Record List
                if (Is_It_Found == false)
                    for (auto var: RecordsList) {
                        if (var.name == PointsTo) {
                            Is_It_Found = true;
                            PointsToAddress = var.Address;
                            RecordSize = var.size;
                            RecordParametersCounter = var.ParameterCounters;
                        }
                    }
                //Record Children
                if (Is_It_Found == false)
                    for (auto var: RecordChildren) {
                        if (var.name == PointsTo /*&& var.rootIndex == RecordIndex*/) {
                            Is_It_Found = true;
                            PointsToAddress = var.Address;
                            RecordSize = var.size;
                            RecordParametersCounter = var.InnerParamterCounter;
                        }
                    }
                //Address List
                if (Is_It_Found == false)
                    for (auto var: AddressList) {
                        if (var.name == PointsTo) {
                            Is_It_Found = true;
                            PointsToAddress = var.Address_;
                        }
                    }
                //Array List
                if (Is_It_Found == false) //DO NOTHING IF WE ARRIVE ARRAY cause syntax of equalization between object and array is illegal
                    for (auto var: ArrayList) {
                        /*if (var.name == PointsTo) {
                            Is_It_Found = true;
                            ArraySize = var.SizeOfArray;
                            PointsToAddress = var.Address_;
                        }*/
                    }

                if (Is_It_Found == false) {
                    PointsToAddress = -1;
                }
            }
            else {
                if(DetectorOfVariable == Simple) {
                    //no p-code is needed when you declare a simple type
                } 
                else if (DetectorOfVariable == Address) {
                    PointsTo = *name_;
                    bool Is_It_Found = false;
                    //SymbolTable
                    if (Is_It_Found == false)
                        for (auto AddressIterator: SymbolTable) {
                            if (AddressIterator.first == PointsTo) {
                                Is_It_Found = true;
                                PointsToAddress = AddressIterator.second.Address;
                            }
                        }
                    //Record List
                    if (Is_It_Found == false)
                        for (auto AddressIterator: RecordsList) {
                            if (AddressIterator.name == PointsTo) {
                                Is_It_Found = true;
                                PointsToAddress = AddressIterator.Address;
                            }
                        }
                    //Record Children
                    if (Is_It_Found == false)
                        for (auto AddressIterator: RecordChildren) {
                            if (AddressIterator.name == PointsTo) {
                                Is_It_Found = true;
                                PointsToAddress = AddressIterator.Address;
                            }
                        }
                    //Address List
                    if (Is_It_Found == false)
                        for (auto AddressIterator: AddressList) {
                            if (AddressIterator.name == PointsTo) {
                                Is_It_Found = true;
                                PointsToAddress = AddressIterator.Address_;
                            }
                        }
                    //Array List
                    if (Is_It_Found == false)
                        for (auto AddressIterator: ArrayList) {
                            if (AddressIterator.name == PointsTo) {
                                Is_It_Found = true;
                                PointsToAddress = AddressIterator.Address_;
                            }
                        }

                    if (Is_It_Found == false) {
                        PointsToAddress = -1;
                    }

                } 
                else if (DetectorOfVariable == Array) {
                    //Array List (Array of type Array(type_->pgencode() called)

                    for (auto var: ArrayList) {
                            if (var.name == *name_) {
                               //PointsToAddress = var.Address_;
                                SizeOfSingleObject = var.SizeOfArray;
                            }
                        }

                } 
                else if (DetectorOfVariable == Record) {
                    //Creating and pointing an object doesn't ouput anything...<>
                    //but it copies it's name,address,and it's size (Extra ParameterCounter)
                    bool Is_It_Found = false;
                    for (auto var: RecordsList) {
                        if (var.name == *name_) {
                            PointsTo = var.name;
                            PointsToAddress = var.Address;
                            RecordSize = var.size;
                            SizeOfSingleObject = var.size;;
                            RecordParametersCounter = var.ParameterCounters;
                            DetectorOfVariable = Record;
                            ArrayTypeDetector = *name_;
                        }
                    }
                }
            }
        }
        else if(Condition == State)
        {
            static int Address_ = 0;
            bool IsFound = false;
            if(DetectorOfVariable == Simple)
            {
                SizeOfSingleObject = 1;
                if(SymbolTable.find(*name_) != SymbolTable.end())
                    os << "ldc " << SymbolTable.at(*name_).Address << endl;
            }
            else if(DetectorOfVariable == Address)
            {
                DataType FoundIn = NoneData;
                if(IsFound == false)
                    for(auto Iterator : SymbolTable)
                {
                    if(Iterator.first == *name_)
                    {
                        FoundIn = SymbolTableData;
                        IsFound = true;
                        Address_ = Iterator.second.Address;
                    }
                }
                if(IsFound == false)
                    for(auto Iterator : RecordsList)
                {
                    if(Iterator.name == *name_)
                    {
                        FoundIn = RecordData;
                        IsFound = true;
                        Address_ = Iterator.Address;
                    }
                }
                if(IsFound == false)
                    for(auto Iterator : RecordChildren)
                {
                    if(Iterator.name == *name_ )
                    {
                        FoundIn = RecordChildrenData;
                        IsFound = true;
                        Address_ = Iterator.Address;
                    }
                }
                if(IsFound == false)
                    for(auto Iterator : AddressList)
                {
                    if(Iterator.name == *name_ && IsFound == false)
                    {
                        FoundIn = AddressData;
                        IsFound = true;
                        Address_ = Iterator.Address_;
                    }
                }
                if(IsFound == false)
                {}
                else
                    os << "ldc " << Address_ << endl;

                SizeOfSingleObject = 1;

                /*if(FoundIn == AddressData)
                    os << "ind" << endl;*/

            }
            else if(DetectorOfVariable == Array)
            {
                //Calling an array and modifying it
                int innerindex = 0;
                for (auto var : ArrayList) {
                    if(var.name == *name_)
                    {
                        os << "ldc " << var.Address_ << endl;
                        ArrayIndex = innerindex;
                        ArraySubpart = var.Subpart;
                    }
                    innerindex++;
                }
            }
            else if(DetectorOfVariable == Record)
            {
                if(IsInsideRecord == OFF)
                {
                    for(auto RecordIterator : SymbolTable)
                    {
                        if(RecordIterator.first == *name_ && IsFound == false)
                        {
                            IsFound = true;
                            Address_ = RecordIterator.second.Address;
                        }
                    }
                    for(auto RecordIterator : RecordsList)
                    {
                        if(RecordIterator.name == *name_ && IsFound == false)
                        {
                            IsFound = true;
                            Address_ = RecordIterator.Address;
                            SizeOfSingleObject = RecordIterator.size;
                        }
                    }
                    os << "ldc " << Address_ << endl;

                }
                if(IsInsideRecord == ON)
                {
                    for(auto Record_Child : RecordChildren)
                    {
                        if(Record_Child.name == *name_ )
                            os << "inc " << Record_Child.offset << endl;
                        SizeOfSingleObject = Record_Child.size;

                    }
                }

            }
        }
        else if(Ind_Flag)
        {
            os << "ind" << endl;
        }
    }
    virtual Object* clone() const { return new IdeType(*this); }

private:
    string* name_;
};

class ArrayType : public Type {
public:
    ArrayType(int l, int u, Object* type) : low_(l), up_(u), type_(type) { assert(type_); }

    ArrayType(const ArrayType& a) : low_(a.low_), up_(a.up_) {
        type_ = a.type_->clone();
    }

    virtual ~ArrayType() {
        if (type_) delete type_;
    }

    void print(ostream& os) {
        os << "Node name : ArrayType: low bound is: " << low_ << ", up bound is: " << up_ << endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        Dimension InputDimension;
        ArraysCounter++;
        DetectorOfVariable = Array;
        if(ArrayName == "")
            ArrayName = CreatedObject;
        CreatedObject = "";
        if(ArraySize == 0)
        {
            ArraySize = ArraySize +  up_ - low_  + 1;
        }
        else
        {
            ArraySize = ArraySize * (up_ - low_  + 1);
        }
        assert(type_);
        InputDimension.Lower_Bound = low_, InputDimension.Upper_Bound = up_;
        ArrayInnerDimensions.push_back(InputDimension);
        IsInsideArray = ON;
        type_->pcodegen(os);
        IsInsideArray = OFF;
        DetectorOfVariable = Array;
    }
    virtual Object* clone() const { return new ArrayType(*this); }

private:
    Object* type_;
    int low_, up_;
};

class RecordType : public Type {
public:
    RecordType(Object* record_list) : record_list_(record_list) { assert(record_list_); }

    RecordType(const RecordType& y) {
        record_list_ = y.record_list_->clone();
    }

    virtual ~RecordType() {
        if (record_list_) delete record_list_;
    }

    void print(ostream& os) {
        os << "Node name : RecordType" << endl;
        assert(record_list_);
        record_list_->print(os);
    }
    void pcodegen(ostream& os) {
        RecordsCounter++; //Resembles a Record Type Counter
        RecordIndex++;  //Current Index of Record Declaration
        if(RecordName != "")
            RecordName = CreatedObject; //Resembles Current Record Name
        ObjectNotCreated = "";
        assert(record_list_);
        DetectorOfVariable = Record;
        record_list_->pcodegen(os);
    }
    virtual Object* clone() const { return new RecordType(*this); }

private:
    Object* record_list_;
};

class AddressType : public Type {
public:
    AddressType(Object* type) : type_(type) { assert(type_); }

    AddressType(const AddressType& t) {
        type_ = t.type_->clone();
    }

    virtual ~AddressType() {
        if (type_) delete type_;
    }

    void print(ostream& os) {
        os << "Node name : AddressType" << endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        AddressesCounter++;
        if(AddressName == "")
        AddressName = CreatedObject;
        CreatedObject = "";
        if (type_)
            assert(type_);
        DetectorOfVariable = Address;
        type_->pcodegen(os);
    }
    virtual Object* clone() const { return new AddressType(*this); }

private:
    Object* type_;
};

class Declaration : public Object {
};

class VariableDeclaration : public Declaration {
public:
    VariableDeclaration(Object* type, const char* str) : type_(type) {
        assert(type_);
        name_ = new string(str);
    }

    VariableDeclaration(const VariableDeclaration& p) {
        type_ = p.type_->clone();
        name_ = new string(*p.name_);
    }

    virtual ~VariableDeclaration() {
        if (type_) delete type_;
        delete name_;
    }

    void print(ostream& os) {
        os << "Node name : VariableDeclaration. Var name is: " << *name_ <<  endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        //for both address and simple and record have to contain a ARRAY DETECTOR (ARRAY OF SIMPLE/ADDRESS/RECORDS/ARRAY!) - Julian Task
        extern map<string, SymbolTableDetails> SymbolTable;
        assert(type_);
        CreatedObject = *name_;
        type_->pcodegen(os);
        static int Offset = 0;
        if(Condition == Declare)
        {
            //The Program has to support All Types of Objects in a Main Record Variable.
            if(IsInsideRecord == ON)
            {
                //CASE 1 - Simple inside Record -> ADD TO Record Child (Add offset, add current address, set current Record Index)
                if(DetectorOfVariable == Simple)
                {
                    RecordChild input;
                    input.name = *name_;
                    input.Address = CurrentAddress;
                    input.size = 1;
                    input.type = Simple;
                    input.offset = Offset;
                    input.rootIndex = RecordIndex;
                    input.PointsToName = "";
                    input.DataTye_ = SimpleData;
                    input.InnerParamterCounter = 0;
                    Offset++;
                    RecordChildren.push_back(input);
                }
                //CASE 2 - Address inside Record -> ADD TO Record Child (Add offset, add current address, set current Record Index )
                // Extra, Find Address Type/Name/Pointer
                else if(DetectorOfVariable == Address)
                {
                    RecordChild input;
                    input.name = *name_;
                    input.Address = CurrentAddress;
                    input.size = 1;
                    input.type = Address;
                    input.offset = Offset;
                    input.rootIndex = RecordIndex;
                    input.InnerParamterCounter = 0;
                    if(PointsToAddress != -1)
                    input.PointsToName = (PointsTo != "") ? PointsTo : "";
                    else input.PointsToName = RecordName; //since a pointer points to an object not fully created then we are talking about a record root
                    RecordChildren.push_back(input);
                    //INSERT Details to AddressList (name & address and size of a inserted pointer)
                    AddressDetails Extra;
                    Extra.name = *name_ , Extra.Address_ = CurrentAddress,Extra.size = 1;
                    //find Address Points To
                    if(PointsTo != "")
                    {
                        Extra.PointsToAddress = PointsToAddress;
                        Extra.PointsTo = PointsTo;
                    }
                    else
                    {
                        Extra.PointsTo = ObjectNotCreated;
                        int FirstAddressOfRecord = CurrentAddress;
                        for(auto var:RecordChildren)
                        {
                            if(var.rootIndex == RecordIndex)
                            {
                                FirstAddressOfRecord = min(FirstAddressOfRecord,var.Address);
                            }
                        }
                        Extra.PointsToAddress = FirstAddressOfRecord;
                    }

                    PointsTo = "";
                    AddressName = "";
                    PointsToAddress = -1;
                    AddressList.push_back(Extra);
                }
                //CASE 3 - Record inside Record -> ADD TO Record Child (Add offset, add current address, set current Record Index )
                // Extra, Find FirstAddress Size/Name . then, set offset & RecordIndex and push to RecordChildren
                else if(DetectorOfVariable == Record)
                {
                    RecordChild input;
                    input.name = *name_;
                    //int SizeOfAll = 0; int FirstAddress; int Counter = 0;
                    /*for (auto Record_Child : RecordChildren)
                    {
                        if (Record_Child.rootIndex == RecordIndex)
                        {
                            Counter++;
                            if (SizeOfAll == 0)
                            {
                                FirstAddress = Record_Child.Address;
                            }
                            SizeOfAll += Record_Child.size;
                        }
                    }*/
                    input.Address = CurrentAddress;
                    input.size = RecordSize;
                    input.type = Record;
                    input.offset = Offset;
                    input.rootIndex = RecordIndex;
                    input.PointsToName = "";
                    input.InnerParamterCounter = RecordParametersCounter;
                    Offset++;
                    RecordChildren.push_back(input);
                    CurrentAddress +=RecordSize;

                }
                //CASE 4 - Array inside Record -> ADD TO Record Child (Add offset, add current address, set current Record Index )
                // Extra, Find FirstAddress Size/Name . then, set offset & RecordIndex and push to RecordChildren
                else if(DetectorOfVariable == Array)
                {
                    RecordChild input;
                    input.name = *name_;
                    input.Address = CurrentAddress;
                    input.size = ArraySize;
                    input.type = Array;
                    input.offset = Offset;
                    input.rootIndex = RecordIndex;
                    Offset++;
                    RecordChildren.push_back(input);

                    ArrayDetails Extra;
                    Extra.name = *name_;
                    Extra.Address_ = CurrentAddress;
                    Extra.SizeOfArray = ArraySize;
                    Extra.Dimensions = (ArrayInnerDimensions);
                    Extra.DataType_ = (SizeOfSingleObject == 1) ? SimpleData : MixedData;

                    ArrayInnerDimensions.clear();
                    //Calculate IXA - Iterate In Reverse and calculate IXA (1, 1 * delta D(n), 1 * delta D(n) * delta D(n-1) ....
                    int Ixa_Result = 1;
                    Extra.IXA_List.push_back(Ixa_Result);
                    int SubpartOfDimensions = 0;
                    for (vector<Dimension>::reverse_iterator i = Extra.Dimensions.rbegin(); i != Extra.Dimensions.rend(); i++ )
                    {
                        SubpartOfDimensions = i->Upper_Bound - i->Lower_Bound + 1;
                        Ixa_Result *= SubpartOfDimensions;
                        Extra.IXA_List.push_back(Ixa_Result);
                    }

                }
            }
            //Simply to Symbol Table.
            else {
                if(DetectorOfVariable == Simple)
                {
                    SymbolTableDetails input;
                    input.Address = CurrentAddress;
                    input.Size = 1;
                    input.Type = Simple;
                    input.relativefunction = 0;
                    SymbolTable.insert(pair<string, SymbolTableDetails>(*name_, input));
                }
                else if(DetectorOfVariable == Address)
                {
                    SymbolTableDetails input;
                    input.Address = CurrentAddress;
                    input.Size = 1;
                    input.Type = Address;
                    SymbolTable.insert(pair<string, SymbolTableDetails>(*name_, input));

                    AddressDetails Extra;
                    Extra.name = *name_ , Extra.Address_ = CurrentAddress,Extra.size = 1;
                    Extra.PointsTo = PointsTo , Extra.PointsToAddress = PointsToAddress;
                    PointsTo = "";
                    PointsToAddress = -1;
                    AddressList.push_back(Extra);
                }
                else if(DetectorOfVariable == Record)
                {
                    SymbolTableDetails input;
                    int SizeOfAll = 0; int FirstAddress; int Counter = 0;
                    for (auto Record_Child : RecordChildren) //assumption this for go to vector like this direction ------>
                    {
                        if (Record_Child.rootIndex == RecordIndex)
                        {
                            Counter++;
                            if (SizeOfAll == 0)
                            {
                                FirstAddress = Record_Child.Address;
                            }
                            SizeOfAll += Record_Child.size;
                        }
                    }

                    input.Address = FirstAddress;
                    input.Size = SizeOfAll;
                    input.Type = Record;
                    SymbolTable.insert(pair<string, SymbolTableDetails>(*name_, input));

                    RecordDetails Extra;
                    Extra.name = *name_;
                    Extra.size = SizeOfAll;
                    Extra.Address = FirstAddress;
                    Extra.ParameterCounters = Counter;
                    RecordsList.push_back(Extra);
                    RecordSize = 0;
                    Offset = 0;
                }
                else if(DetectorOfVariable == Array)
                {
                    SymbolTableDetails input;
                    input.Address = CurrentAddress;
                    input.Type = Array;
                    int integer = 0;
                    if(ArrayTypeDetector == "Integer")
                    {
                        integer = 1;
                        input.Size = ArraySize * integer;
                    }
                    else
                    {
                        for(auto var:RecordsList)
                        {
                            if(var.name == CreatedObject)
                            {
                                input.Size = ArraySize * var.size;
                            }
                        }
                    }
                    ArrayTypeDetector = "";
                    SymbolTable.insert(pair<string, SymbolTableDetails>(*name_, input));

                    ArrayDetails Extra;
                    Extra.DataType_ = (integer==1) ? SimpleData : MixedData;
                    Extra.name = *name_ , Extra.Address_ = CurrentAddress,Extra.SizeOfArray = input.Size ,Extra.Type = Array;
                    Extra.Dimensions = ArrayInnerDimensions;
                    ArrayInnerDimensions.clear();
                    //Calculate IXA AND inserting to IXA Stack!
                    int Ixa_Result = 1;
                    Extra.IXA_List.push_back(Ixa_Result);
                    int SubpartOfDimensions = 0;
                    for (vector<Dimension>::reverse_iterator i = Extra.Dimensions.rbegin(); i != Extra.Dimensions.rend(); i++ )
                    {
                        SubpartOfDimensions = i->Upper_Bound - i->Lower_Bound + 1;
                        Ixa_Result *= SubpartOfDimensions;
                        Extra.IXA_List.push_back(Ixa_Result);
                    }
                    int MultiplicationOfAllIXA = Extra.IXA_List.back();
                    Extra.IXA_List.pop_back();

                    //Calculate Subpart AND inserting to Extra.Subpart
                    int LastLowerBound = Extra.Dimensions.at(Extra.Dimensions.size() - 1).Lower_Bound;
                    int Subpart = 0;
                    for(auto var : Extra.Dimensions)
                    {
                        int difference = var.Upper_Bound - var.Lower_Bound + 1;
                        int l = var.Lower_Bound;
                        Subpart += l* MultiplicationOfAllIXA/difference;
                        MultiplicationOfAllIXA/=difference;
                    }
                    Subpart *= SizeOfSingleObject;
                    Extra.Subpart = Subpart;
                    ArrayList.push_back(Extra);

                    CurrentAddress = CurrentAddress + ArraySize;

                }
            }

            if (DetectorOfVariable != Record && DetectorOfVariable != Array )
            {
                CurrentAddress += 1;
                ParameterCounter += 1;
            }
            /*if(RecordInRecord == ON && ArrayInArray == ON)
            {
                CurrentAddress += 1;
                ParameterCounter += 1;
            }*/
        }
        CreatedObject = "";

    }

    virtual Object* clone() const { return new VariableDeclaration(*this); }

private:
    Object* type_;
    string* name_;
};

class Parameter : public Object {
public:
    Parameter(Object* type, const char* name) : type_(type) {
        assert(type_);
        name_ = new string(name);
    }

    Parameter(const Parameter& p) {
        type_ = p.type_->clone();
        name_ = new string(*p.name_);
    }

    virtual ~Parameter() {
        if (type_) delete type_;
        delete name_;
    }

    void print(ostream& os) {
        printWayOfPassing(os);
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(type_);
        type_->pcodegen(os);
        os << "Parameter name :" << *name_ << " proc/func name is " << currentFuncOrProcName << endl;
        if(Condition == Declare)
        {
            if(DetectorOfVariable == Simple)
            {
                {
                    OperationParameter input;
                    input.Address = CurrentAddress;
                    input.Type = Simple;
                    input.Size = 1;
                    input.OperationRootIndex = OperationIndex;
                    input.OperationName = OperationName;
                    OperationParametersList.push_back(input);
                }
                //Do other stuff if needed!
            }
            if(DetectorOfVariable == Address)
            {
                {
                    OperationParameter input;
                    input.Address = CurrentAddress;
                    input.Type = Address;
                    input.Size = 1;
                    input.OperationRootIndex = OperationIndex;
                    input.OperationName = OperationName;
                    OperationParametersList.push_back(input);
                }
                //Do other stuff if needed!

            }
            if(DetectorOfVariable == Array)
            {
                {
                    OperationParameter input;
                    input.Address = CurrentAddress;
                    input.Type = Simple;
                    input.Size = 1;
                    input.OperationRootIndex = OperationIndex;
                    input.OperationName = OperationName;

                    OperationParametersList.push_back(input);

                }
                //Do other stuff if needed!
            }
            if(DetectorOfVariable == Record)
            {
                {
                    OperationParameter input;
                    input.Address = CurrentAddress;
                    input.Type = Simple;
                    input.Size = 1;
                    input.OperationRootIndex = OperationIndex;
                    input.OperationName = OperationName;

                    OperationParametersList.push_back(input);

                }
                //Do other stuff if needed!
            }
        }
        if(Condition == State)
        {
            if(DetectorOfVariable == Simple)
            {
                for(auto var : OperationParametersList)
                {
                    if(var.Name == *name_)
                    {
                        os << "lda " << var.OperationRootIndex << " " << var.Address << endl;
                    }
                }
            }
            if(DetectorOfVariable == Address)
            {
                for(auto var : OperationParametersList)
                {
                    if(var.Name == *name_)
                    {
                        os << "lda " << var.OperationRootIndex << " " << var.Address << endl;
                        os << "ind" << endl;
                    }
                }

            }
            if(DetectorOfVariable == Array)
            {

            }
            if(DetectorOfVariable == Record)
            {

            }
        }

    }
protected:
    virtual void printWayOfPassing(ostream& os) const = 0;

private:
    Object* type_;
    string* name_;
};

class ByReferenceParameter : public Parameter {
public:
    ByReferenceParameter(Object* type, const char* name) : Parameter(type, name) {}
    virtual Object* clone() const { return new ByReferenceParameter(*this); }
    void pcodegen(ostream& os) {
        SymbolTableDetails input;
        input.Address = CurrentAddress;
        input.Size = 1;
        input.Type = Simple;
        input.relativefunction = 0;
        //SymbolTable.insert(pair<string, SymbolTableDetails>(name, input));
    }
protected:
    void printWayOfPassing(ostream& os) const {
        os << "Node name : ByReferenceParameter ";
    }
};

class ByValueParameter : public Parameter {
public:
    ByValueParameter(Object* type, const char* name) : Parameter(type, name) {}
    virtual Object* clone() const { return new ByValueParameter(*this); }
protected:
    void printWayOfPassing(ostream& os) const {
        os << "Node name : ByValueParameter " ;
    }
};

class ParameterList : public Object {
public:
    ParameterList(Object* formal) : formal_(formal), formal_list_(NULL) { assert(formal_); }
    ParameterList(Object* formal, Object* formal_list) : formal_(formal), formal_list_(formal_list) { assert(formal_ && formal_list_); }

    ParameterList(const ParameterList& pl) {
        formal_ = pl.formal_->clone();
        formal_list_ = pl.formal_list_->clone();
    }

    virtual ~ParameterList() {
        if (formal_) delete formal_;
        if (formal_list_) delete formal_list_;
    }

    void print(ostream& os) {
        os << "Node name : ParameterList" << endl;
        if (formal_list_) {
            formal_list_->print(os);
        }
        assert(formal_);
        formal_->print(os);
    }
    void pcodegen(ostream& os) {
        paramterlistcounter ++;
        if (formal_list_) {
            Condition = Declare;
            formal_list_->pcodegen(os);
            Condition = NONE;
        }
        OperationParameterCounter++; //Counts ParametersInside Operation!
        assert(formal_);
        Condition = Declare;
        formal_->pcodegen(os);
        Condition = NONE;
    }
    virtual Object* clone() const { return new ParameterList(*this); }

private:
    Object* formal_;
    Object* formal_list_;
};

class FunctionDeclaration : public Declaration {
public:
    FunctionDeclaration(Object* type, Object* block, const char* name) : type_(type), block_(block), formal_list_(NULL) {
        assert(type_ && block_);
        name_ = new string(name);
    }

    FunctionDeclaration(Object* type, Object* formal_list, Object* block, const char* name) : type_(type), formal_list_(formal_list), block_(block) {
        assert(type_ && formal_list_ && block_);
        name_ = new string(name);
    }

    virtual ~FunctionDeclaration() {
        if (type_) delete type_;
        if (block_) delete block_;
        if (formal_list_) delete formal_list_;
        if (name_) delete name_;
    }

    FunctionDeclaration(const FunctionDeclaration& fd) {
        type_ = fd.type_->clone();
        block_ = fd.block_->clone();
        formal_list_ = fd.formal_list_->clone();
        name_ = new string(*fd.name_);
    }

    void print(ostream& os) {
        os << "Node name : FunctionDeclaration. Func name is: " << *name_ << endl;
        assert(type_ && block_);
        type_->print(os);
        if (formal_list_) {
            formal_list_->print(os);
        }
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        if(OperationIndex == -1) //Latest Call was from Program - We arrived to Procedure from Program
        {
            os << "ssp " << CurrentAddress << endl;
            //os << "ssp " << 5 + ParameterCounter << endl;
            os << "sep " << 50 << endl;
            os << "ujp "  << ProgramName << "_begin" << endl;
        }
        if(OperationName == "")
            OperationName = *name_;
        OperationIndex++;
        OperationType_ = Function;
        os << *name_ << ":" << endl;
        OperationParameterCounter = 0;
        assert(type_ && block_);
        type_->pcodegen(os);
        if (formal_list_) {
            formal_list_->pcodegen(os);
        }
        OperationIndex--;
        block_->pcodegen(os);
    }
    virtual Object* clone() const { return new FunctionDeclaration(*this); }

private:
    Object* type_;
    Object* block_;
    Object* formal_list_;
    string* name_;
};

class ProcedureDeclaration : public Declaration {
public:
    ProcedureDeclaration(Object* block, const char* name) : formal_list_(NULL), block_(block) {
        assert(block_);
        name_ = new string(name);
    }

    ProcedureDeclaration(Object* formal_list, Object* block, const char* name) : formal_list_(formal_list), block_(block) {
        assert(formal_list_ && block_);
        name_ = new string(name);
    }

    virtual ~ProcedureDeclaration() {
        if (block_) delete block_;
        if (formal_list_) delete formal_list_;
        if (name_) delete name_;
    }

    ProcedureDeclaration(const ProcedureDeclaration& pd) {
        block_ = pd.block_->clone();
        formal_list_ = pd.formal_list_->clone();
        name_ = new string(*pd.name_);
    }

    void print(ostream& os) {
        os << "Node name : ProcedureDeclaration. Proc name is: " << *name_ << endl;
        assert(block_);
        if (formal_list_) {
            formal_list_->print(os);
        }
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        currentFuncOrProcName = *name_;
        if(OperationIndex == -1) //Latest Call was from Program - We arrived to Procedure from Program
        {
            os << "ssp " << CurrentAddress << endl;
            //os << "ssp " << 5 + ParameterCounter << endl;
            os << "sep " << 50 << endl;
            os << "ujp "  << ProgramName << "_begin" << endl;
        }
        if(OperationName == "")
            OperationName = *name_;
        OperationIndex++;
        OperationType_ = Procedure;
        os << *name_ << ":" << endl;
        OperationParameterCounter = 0;
        assert(block_);
        if (formal_list_) {
            formal_list_->pcodegen(os);
        }
        //Inserting Operation Data to OperationList
        {
            Operation input;
            input.name = OperationName;
            input.Type = OperationType_;
            input.ParametersCounter = OperationParameterCounter;
            OperationList.push_back(input);
        }
        //Print Operation SSP/SEP/UJP
        {
            os << "ssp " << 5 + OperationParameterCounter << endl;
            //os << "ssp " << 5 + ParameterCounter << endl;
            os << "sep " << 50 << endl;
            os << "ujp "  << *name_ << "_begin" << endl;
        }
        os << *name_ << "_begin :" << endl;
        block_->pcodegen(os);
        OperationIndex--;
        os << "retf" << endl;
    }
    virtual Object* clone() const { return new ProcedureDeclaration(*this); }

private:
    Object* block_;
    Object* formal_list_;
    string* name_;
};

class DeclarationList : public Object {
public:
    DeclarationList(Object* decl) : decl_(decl), decl_list_(NULL) { assert(decl_); }
    DeclarationList(Object* decl_list, Object* decl) : decl_list_(decl_list), decl_(decl) { assert(decl_list_ && decl); }

    DeclarationList(const DeclarationList& dl) {
        decl_ = dl.decl_->clone();
        decl_list_ = dl.decl_list_->clone();
    }

    virtual ~DeclarationList() {
        if (decl_) delete decl_;
        if (decl_list_) delete decl_list_;
    }

    void print(ostream& os) {
        os << "Node name : DeclarationList" << endl;
        if (decl_list_) {
            decl_list_->print(os);
        }
        assert(decl_);
        decl_->print(os);
    }
    void pcodegen(ostream& os) {

        if (decl_list_) {
            Condition = Declare;
            decl_list_->pcodegen(os);
            Condition = NONE;
        }
        assert(decl_);
        Condition = Declare;
        decl_->pcodegen(os);

        Condition = NONE;

    }
    virtual Object* clone() const { return new DeclarationList(*this); }

private:
    Object* decl_;
    Object* decl_list_;
};

class Block : public Object {
public:
    Block(Object* stat_seq) : stat_seq_(stat_seq), decl_list_(NULL) { assert(stat_seq_); }
    Block(Object* decl_list, Object* stat_seq) : decl_list_(decl_list), stat_seq_(stat_seq) { assert(decl_list_ && stat_seq_); }

    Block(const Block& b) {
        decl_list_ = b.decl_list_->clone();
        stat_seq_ = b.stat_seq_->clone();
    }

    virtual ~Block() {
        if (stat_seq_) delete stat_seq_;
        if (decl_list_) delete decl_list_;
    }

    void print(ostream& os) {
        os << "Node name : Begin" << endl;
        if (decl_list_) {
            decl_list_->print(os);
        }

        assert(stat_seq_);
        stat_seq_->print(os);
    }
    void pcodegen(ostream& os) {
        if (decl_list_) {
            decl_list_->pcodegen(os);
        }
        assert(stat_seq_);
        if(OperationIndex == -1)
            os << ProgramName << "_begin :" << endl;
        stat_seq_->pcodegen(os);
    }

    virtual Object* clone() const { return new Block(*this); }

private:
    Object* decl_list_;
    Object* stat_seq_;
};

class Program : public Object {
public:
    Program(Object* block, const char* str) : block_(NULL) {
        block_ = dynamic_cast<Block*>(block);
        assert(block_);
        name_ = new string(str);
    }

    Program(const Program& prog) {
        block_ = dynamic_cast<Block*>(prog.block_->clone());
        assert(block_);
        name_ = new string(*prog.name_);
    }

    virtual ~Program() {
        if (block_) delete block_;
        delete name_;
    }

    void print(ostream& os) {
        os << "Node name : Root/Program. Program name is: " << *name_ << endl;
        assert(block_);
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        ProgramName = *name_;
        os << ProgramName << ":" << endl;
        assert(block_);
        block_->pcodegen(os);
        os << "stp" << endl;

    }
    virtual Object* clone() const { return new Program(*this); }

private:
    Block* block_;
    string* name_;
};

#endif //AST_H