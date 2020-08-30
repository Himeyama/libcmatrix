#include <iostream>
#include <vector>

template <typename NUM>
class Vector{
    public:
        NUM* vector;
        int size;

        Vector(){}

        Vector(int n){
            size = n;
            vector = new NUM[n];
            for(int i = 0; i < n; i++)
                vector[i] = 0;
        }

        void del(){
            delete[] vector;
        }

        std::string inspect(){
            std::string s = "[";
            for(int i = 0; i < size; i++){
                s += std::to_string(vector[i]) + (i == size - 1 ? "]" : ", ");
            }
            return s;
        }

        Vector p(){
            std::cout << inspect() << std::endl;
            return *this;
        }

        Vector copy(){
            Vector vec(size);
            for(int i = 0; i < size; i++)
                vec[i] = vector[i];
            return vec;
        }

        NUM & operator [](int i){
            return vector[i];
        }
};

template <typename NUM>
class Matrix{
    public: 
        Vector<NUM>* matrix;
        int size;

        Matrix(int n){
            size = n;
            matrix = new Vector<NUM>[n];
            for(int i = 0; i < n; i++){
                matrix[i] = Vector<NUM>(n);
                matrix[i].size = n;
            }
        }

        Matrix(int r, int c){
            size = r;
            matrix = new Vector<NUM>[r];
            for(int i = 0; i < c; i++){
                matrix[i] = Vector<NUM>(c);
                matrix[i].size = c;
            }

        }

        void del(){
            for(int i = 0; i < size; i++)
                matrix[i].del();
            delete[] matrix;
        }

        std::string inspect(){
            std::string s;
            s = "[\n";
            for(int r = 0; r < size; r++){
                s += "    [";
                for(int c = 0; c < matrix[0].size; c++){
                    s += std::to_string(matrix[r][c]) + (matrix[0].size == c + 1 ? "" : ", ");
                }
                s += (std::string)"]" + (size == r + 1 ? "" : ",") + "\n";
            }
            s += "]";
            return s;
        }

        Matrix p(){
            std::cout << inspect() << std::endl;
            return *this;
        }

        // 行列のコピー
        Matrix copy(){
            Matrix mat(size, matrix[0].size);
            for(int i = 0; i < size; i++)
                for(int j = 0; j < matrix[0].size; j++)
                    mat.matrix[i][j] = matrix[i][j];
            return mat;
        }

        // 単位行列
        static Matrix identity(int n){
            Matrix mat(n);
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    mat.matrix[i][j] = i == j ? 1 : 0;
            return mat;
        }

        // 逆行列
        Matrix inv(){
            int n = size;
            Matrix matrix = copy();
            Matrix e = identity(n);
            for(int i = 0; i < n - 1; i++){
                NUM ii = matrix.matrix[i][i];
                for(int j = i + 1; j < n; j++){
                    NUM ji = matrix.matrix[j][i];
                    for(int k = 0; k < n; k++){
                        matrix.matrix[j][k] -= ji / ii * matrix.matrix[i][k];
                        e.matrix[j][k] -= ji / ii * e.matrix[i][k];
                    }
                }
            }

            for(int i = n - 1; i >= 1; i--){
                NUM p = matrix.matrix[i][i];
                for(int k = 0; k < n; k++){
                    matrix.matrix[i][k] /= p;
                    e.matrix[i][k] /= p;
                }

                for(int j = i - 1; j >= 0; j--){
                    NUM p = -matrix.matrix[j][i];
                    for(int k = 0; k < n; k++){
                        matrix.matrix[j][k] += p * matrix.matrix[i][k];
                        e.matrix[j][k] += p * e.matrix[i][k];
                    }
                }
            }
            matrix.del();
            return e;
        }

};