//
//  main.cpp
//  lab1oopip
//
//  Created by Ульяна Тозик on 19.02.24.
//

#include <iostream>
#include <iomanip>

using namespace std;

class matrix //класс, содержащий информацию о матрицах
{
   int rows;
   int cols;
   float** elements;
   

public:
    static float sum;
    matrix(int r, int c);
    matrix(const matrix& second);
    matrix();
    ~matrix();
    void enter_elements();
    void print_elements();
    void m_umno(const matrix& second);
    void m_vichit(const matrix& second);
    float m_max(int x, int y);
    static void calculate_sum(const matrix& mat1, const matrix& mat2);
};


matrix::matrix(int rows, int cols) : rows(rows),cols(cols) //конструктор
{
    elements= new float*[rows];
        for(int i=0;i<rows;i++)
        {
            elements[i]= new float[cols];
        }

}

matrix::matrix(): rows(0), cols(0){} //конструктор без параметров

matrix::matrix(const matrix& second):rows(second.rows),cols(second.cols) //конструктор копирования
{
    elements=new float*[rows];
    for(int i=0;i<rows;i++){
        elements[i]=new float[cols];
        for(int j=0;j<cols;j++){
            elements[i][j]=second.elements[i][j];
        }
    }
}

matrix::~matrix() //деструктор
{
    for(int i=0; i<rows; i++)
    {
        delete[] elements[i];
    }
        delete[] elements;
         
}

void matrix:: m_umno(const matrix& second) //метод умножения 2 матриц
{

       matrix result(rows, second.cols);

       for(int i=0;i<rows;i++)
       {
          for(int j=0;j<second.cols;j++)
          {
            result.elements[i][j]=0;
            for(int k=0;k<cols;k++)
            {
                result.elements[i][j]+=elements[i][k]*second.elements[k][j];
            }
          }
       }

       for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                cout<<result.elements[i][j]<<" ";
            }
            cout<<endl;
        }

        
        
}

void matrix:: m_vichit(const matrix& second) //метод вычитания 2 матрицы из 1
    {
        matrix result(rows,cols);

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                result.elements[i][j]=elements[i][j]-second.elements[i][j];
            }
        }

        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                cout<<result.elements[i][j]<<" ";
            }
            cout<<endl;;
        }
         
    }

float matrix::m_max(int x, int y) //метод поиска в 1 матрице максимального элемента после заданного
{
        if(x<0 || x>rows || y<0 || y>cols)
        {
          cout<<"Введены неверные индексы\n"<<endl;
          return 0;
        }
    
        else
        {
             
            float nextmax=-1;
            
            for(int i=x;i<rows;i++)
            {
                int start_col = (i==x)?y+1:0;
                for(int j=start_col;j<cols;j++)
                {
                    if(elements[i][j] > nextmax)
                    {
                        nextmax=elements[i][j];
                    }
                }
            }
            
            if(nextmax==-1){
                cout<<"Указанный элемент - последний в матрице";
                return 0;
            }
            
            return nextmax;
            
             
        }
    
}
 

void matrix::enter_elements() //метод ввода элементов матрицы
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            std::cout <<"Введите элемент ["<< i <<"]["<< j <<"]: ";
            std::cin >> elements[i][j];
        }
    }
}

void matrix::print_elements() //метод вывода элементов матрицы
{
     
    for(int i=0;i<rows;i++){

        for(int j=0;j<cols;j++)
        {
            std::cout<< elements[i][j] <<" ";
        }
        std::cout << std::endl;
    }

}

float matrix::sum=0;

void matrix::calculate_sum(const matrix& mat1, const matrix& mat2){ //метод поиска суммы всех элементов матриц
    sum=0;
    for(int i=0;i<mat1.rows;i++){
        for(int j=0;j<mat1.cols;j++){
            sum+=mat1.elements[i][j]+mat2.elements[i][j];
        }
    }

}

 

int main(){
    
    const int num_matrices=2;
    matrix matrices[num_matrices]= {matrix(2,2), matrix(2,2)}; //массив объектов класса
    {
        matrix matrix1;
        int row=4,col=3;
        matrix matrix2(row,col);
        matrix *matrix3 = new matrix();
    }
    for(int i=0;i<num_matrices;i++){
        cout<<"\nПеред началом работы введите элементы матрицы\n";
        matrices[i].enter_elements();
    }
    
    int choice=0;
    
    do{
        
        cout<<"\nМеню\n";
        cout<<"1. Вывести элементы матриц\n";
        cout<<"2. Умножить матрицы\n";
        cout<<"3. Вычесть вторую матрицу из первой\n";
        cout<<"4. Найти сумму всех элементов двух матриц\n";
        cout<<"5. Найти максимальный элемент после заданного\n";
        cout<<"6. Выйти из программы\n";
        
        cin>>choice;
        cout<<"\n";
        
        switch(choice)
        {
            case 1: 
            {
                for(int i=0;i<num_matrices;i++)
                {
                    cout<<"Матрица  "<<i+1<<":\n";
                    matrices[i].print_elements();
                }
                break;
            }
            case 2: 
            {
                matrices[0].m_umno(matrices[1]);
                break;
            }
            case 3: 
            {
                matrices[0].m_vichit(matrices[1]);
                break;
            }
            case 4: 
            {
                matrix::calculate_sum(matrices[0], matrices[1]);
                cout<<"\nСумма всех элементов двух матриц: "<< matrix::sum <<endl;
                break;
            }
            case 5: 
            {
                int x,y;
                cout<<"\nВведите индексы элемента 1 матрицы, после которого надо найти     максимальный:\n"<<endl;
                cin >> x >> y;
                int nextmax=matrices[0].m_max(x,y);
                cout<<"\nНаибольший элемент, следующий за указанным: "<< nextmax <<endl;
                break;
            }
            case 6: 
            {
                return 0;
            }
            default: 
            {
                printf("\nВведено неверное значение. Попробуйте снова\n");
            }
        }
    }while(choice!=6);


}
   
 


