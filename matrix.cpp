#include <iostream>
#include <vector>
#include <sstream>

template <typename NUM>
class Vector{
    public:
        std::vector<NUM> vector;

        Vector(){}

        Vector(int n){
            vector.resize(n);
        }

        std::string inspect(){
            std::stringstream ss;
            ss << "[";
            for(int i = 0; i < size(); i++){
                ss << vector[i] << (i == size() - 1 ? "]" : ", ");
            }
            return ss.str();
        }

        int size(){
            return vector.size();
        }

        Vector p(){
            std::cout << inspect() << std::endl;
            return *this;
        }

        Vector copy(){
            Vector vec(size());
            for(int i = 0; i < size(); i++)
                vec[i] = vector[i];
            return vec;
        }

        NUM & operator [](int i){
            if(i >= size())
                std::cerr << "\033[31m警告: アクセスできる範囲を超えています\033[0m" << std::endl;
            return vector[i];
        }

        NUM operator *(Vector vec){
            NUM sum = 0;
            for(int i = 0; i < size(); i++)
                sum += vector[i] * vec[i];
            return sum; 
        }

        Vector(std::initializer_list<NUM> list){
            vector = list;
            int i = 0;
            for(int value: list)
                vector[i++] = value;
        }

};

template <typename NUM>
class Matrix{
    public: 
        std::vector<Vector<NUM>> matrix;

        Matrix(int n){
            matrix.resize(n);
            for(int i = 0; i < n; i++)
                matrix[i].vector.resize(n);
        }

        Matrix(int r, int c){
            matrix.resize(r);
            for(int i = 0; i < c; i++)
                matrix[i].vector.resize(c);
        }

        std::string inspect(){
            std::stringstream ss;
            ss << "[\n";
            for(int r = 0; r < matrix.size(); r++){
                ss << "    [";
                for(int c = 0; c < matrix[0].size(); c++){
                    ss << matrix[r][c] << (matrix[0].size() == c + 1 ? "" : ", ");
                }
                ss << "]" << (matrix.size() == r + 1 ? "" : ",") << "\n";
            }
            ss << "]";
            return ss.str();
        }

        Matrix p(){
            std::cout << inspect() << std::endl;
            return *this;
        }

        // 行列のコピー
        Matrix copy(){
            Matrix mat(matrix.size(), matrix[0].size());
            for(int i = 0; i < matrix.size(); i++)
                for(int j = 0; j < matrix[0].size(); j++)
                    mat[i][j] = matrix[i][j];
            return mat;
        }

        // 単位行列
        static Matrix identity(int n){
            Matrix mat(n);
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    mat[i][j] = i == j ? 1 : 0;
            return mat;
        }

        // 逆行列
        Matrix inv(){
            int n = matrix.size();
            Matrix matrix = copy();
            Matrix e = identity(n);
            for(int i = 0; i < n - 1; i++){
                NUM ii = matrix[i][i];
                for(int j = i + 1; j < n; j++){
                    NUM ji = matrix[j][i];
                    for(int k = 0; k < n; k++){
                        matrix[j][k] -= ji / ii * matrix[i][k];
                        e[j][k] -= ji / ii * e[i][k];
                    }
                }
            }

            for(int i = n - 1; i >= 1; i--){
                NUM p = matrix[i][i];
                for(int k = 0; k < n; k++){
                    matrix[i][k] /= p;
                    e[i][k] /= p;
                }
                for(int j = i - 1; j >= 0; j--){
                    NUM p = -matrix[j][i];
                    for(int k = 0; k < n; k++){
                        matrix[j][k] += p * matrix[i][k];
                        e[j][k] += p * e[i][k];
                    }
                }
            }
            return e;
        }

        // LU分解 U
        Matrix u(){
            Matrix u = copy();
            int n = matrix.size();
            for(int i = 0; i < n - 1; i++){
                NUM ii = u[i][i];
                for(int j = i + 1; j < n; j++){
                    NUM ji = u[j][i];
                    for(int k = 0; k < n; k++)
                        u[j][k] -= ji / ii * u[i][k];
                }
            }
            return u;
        }

        Matrix l(){
            return *this * u().inv();
        }

        int size(){
            return matrix.size();
        }

        NUM det(){
            Matrix m = u().copy();
            NUM sum = 1;
            for(int i = 0; i < size(); i++)
                sum *= m[i][i];
            return sum;
        }

        NUM tr(){
            NUM sum = 0;
            for(int i = 0; i < size(); i++)
                sum += matrix[i][i];
            return sum;
        }

        void about(){
            std::cout << "行列: A = " << inspect() << std::endl
            << "次元: " << size() << " x " << matrix[0].size() << std::endl
            << "行列式: det(A) = " << det() << std::endl
            << "逆行列: inv(A) = " << inv().inspect() << std::endl
            << "下三角行列: L = " << l().inspect() << std::endl
            << "上三角行列: U = " << u().inspect() << std::endl
            << "対角和: tr(A) = " << tr() << std::endl;
        }

        Matrix operator *(Matrix b){
            Matrix a(matrix.size(), matrix[0].size());
            for(int i = 0; i < matrix.size(); i++)
                for(int j = 0; j < matrix[0].size(); j++){
                    a[i][j] = 0;
                    for(int k = 0; k < matrix[0].size(); k++)
                        a[i][j] += matrix[i][k] * b[k][j];
                }
            return a;
        }

        Matrix operator +(Matrix b){
            Matrix a = copy();
            for(int i = 0; i < matrix.size(); i++)
                for(int j = 0; j < matrix[0].size(); j++)
                    a[i][j] += b[i][j];
            return a;
        }

        Vector<NUM> & operator [](int i){
            return matrix[i];
        }

        Matrix(std::initializer_list<Vector<NUM>> list){
            int i = 0;
            matrix.resize(list.size());
            for(Vector<NUM> value: list)
                matrix[i++] = value;
        }
};