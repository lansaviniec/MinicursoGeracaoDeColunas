/** ----------------------------------------------------------------------------
Minicurso: Implementacao de geracao de colunas usando CPLEX em linguagem C/C++
Descricao: Framework para implementacao de geracao de colunas (GC)
Autores: Landir Saviniec e Luiz Henrique Cherri

Obs: Este arquivo implementa a parte generica do framework, devendo o usuario
implementar a parte especifica do problema a ser tratado. Para exemplos,
veja as implementacoes disponiveis nos arquivos pcu.zip e pdl.zip
-----------------------------------------------------------------------------**/

#include <iostream>
#include <vector>
#include <pthread.h>
#include <ilcplex/ilocplex.h>

//declaracao das estruturas para armazenar os dados de entrada
int N_SUB;  //quantidade de subproblemas, definido de acordo com os dados da instancia

//declaracao das classes Subproblema e Mestre
class Subproblema;
class Mestre;

class Modelo
{
    //esta classe implementa as ferramentas do cplex, modelo e resolvedor

    public:

        IloEnv env;  //ambiente do cplex
        IloModel model;  //modelo
        IloCplex cplex;  //cplex
        IloObjective objective;   //expressao da funcao objetivo

        //construtores----------
        Modelo(){
			//chamado quando o modelo e criado
            env = IloEnv();  //cria o ambiente
            model = IloModel(env);   //cria o modelo
            cplex = IloCplex(env);   //cria o cplex
        }

        ~Modelo(){
			//chamado quando o modelo e destruido
            model.end();   //destroi o ambiente
            cplex.end();   //destroi o modelo
            env.end();   //destroi o cplex
        }

        //metodos----------
        void setStream(std::ostream& st){
			//habilita o log do cplex
            cplex.setOut(st);
        }

        void setStreamOff(){
			//desabilita o log do cplex
            cplex.setOut(env.getNullStream());
        }

        void solve(){
			//invoca o cplex
			cplex.solve();
        }

        IloNum getObjective(){
			//retorna o valor da funcao objetivo
            return cplex.getObjValue();
        }

        IloCplex::CplexStatus getStatus(){
			//retorna o estado do cplex
            return this->cplex.getCplexStatus();
        }
};

class Mestre : public Modelo  //herda a implementacao da classe 'Modelo'
{
	//esta classe implementa o problema mestre

    public:
		//declaracao das variaveis e ranges

        //construtores----------
        Mestre(){
			//chamado quando o PM e criado
            this->objective = IloMinimize(this->env);

            this->criar_modelo();
            this->model.add(this->objective);
            this->cplex.extract(this->model);
        }

        ~Mestre(){
			//chamado quando o PM e destruido
		}

		//metodos----------
        void criar_modelo(){
            //criar array de variaveis e coeficientes

            //criar Ranges
        }

		//declaracao do metodo que adiciona uma coluna ao PM,
		//usando o subproblema passado como argumento
        void adicionar_coluna(Subproblema* sub);

        void criar_colunas_artificiais(){
			//metodo para inicializar o mestre
        }
};

class Subproblema : public Modelo  //herda a implementacao da classe 'Modelo'
{
	//esta classe implementa o(s) problema(s)

	public:

		//declaracao das variaveis
        int i;  //variavel para identificar o indice do subproblema

        //construtores----------
        Subproblema(int index){
			//chamado quando o subproblema e criado
            this->objective = IloMinimize(this->env);

            this->i = index;
            this->criar_modelo();

            this->model.add(this->objective);
            this->cplex.extract(this->model);
        }

        ~Subproblema(){
			//chamado quando o subproblema e destruido
		}

        //metodos----------
        void criar_modelo(){
            //definir as variaveis do modelo

            //definir as restricoes do modelo
        }

        void update_objective(Mestre* mestre){
            //atualiza a funcao objetivo do subproblema
        }

        double get_custo_coluna(){
            //calcula o custo da coluna
        }
};

void Mestre::adicionar_coluna(Subproblema* sub){
	//implementacao do metodo que adiciona uma coluna ao PM
}

void ler_dados(std::string arquivo){

    std::ifstream in(arquivo.c_str());
    //codigo para ler os dados de entrada
}

int main(int argc, char* argv[]){
	//parametros: nome do arquivo de dados

    if(argc != 2){
        std::cout << "Argumento invalido." << std::endl;
        return 0;
    }

    ler_dados(argv[1]);  //leitura de dados

    std::cout << "\n== Geracao de colunas ========\n" << std::endl;

    //cria o mestre
    Mestre mestre;
    mestre.setStreamOff();  //desabilita stream cout
    mestre.criar_colunas_artificiais();

    //cria os subproblemas
    std::vector<Subproblema*> Sub;
    for(auto i=0; i<N_SUB; i++){
        Subproblema* sub = new Subproblema(i);
        sub->setStreamOff();  //desabilita stream cout
        Sub.push_back(sub);
    }

    //algoritmo de geracao de colunas
    std::vector<double> custoSub(N_SUB, 0.0);
    const double EPS = 1.0e-5;
    int novaColuna = 0;
    int iter = 0;

    do{

        iter++;
        std::cout << "Iteracao " << iter << std::endl;

        //resolver o mestre
        mestre.solve();
        std::cout << std::setprecision(10) << "Mestre = " << mestre.getObjective() << std::endl;

        novaColuna = 0;

        //resolver os subproblemas
        for(auto i=0; i<N_SUB; i++){
            Sub[i]->update_objective(&mestre);
            Sub[i]->solve();
            custoSub[i] = Sub[i]->getObjective();
        }

        //verificar se os custos reduzidos são negativos
        for(auto i=0; i<N_SUB; i++){
            //adicionar colunas cujos custos reduzidos são negativos
            if(custoSub[i] < -EPS){
                mestre.adicionar_coluna(Sub[i]);
                novaColuna++;
            }
        }

        std::cout << std::endl;
    }while(novaColuna > 0);

    double gc = mestre.getObjective();
    std::cout << std::setprecision(10) << "GC = " << gc << std::endl;

    for(auto i=0; i<N_SUB; i++){
        delete Sub[i];
    }

    return 0;
}
