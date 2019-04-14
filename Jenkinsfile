pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
    }

    // no default agent - need to be specified per stage
    agent none

    stages {
        stage('Docker'){
            agent any
            steps{
                script{
                    // build docker image from dockerfile
                    sh 'docker build -t ${registry} .'
                    // publish image on docker hub
                    if (env.BRANCH_NAME == "develop"){
                        docker.withRegistry( '', registryCredential ) {
                            sh 'docker push ${registry}:latest'
                        }
                    } else {
                        sh 'echo "Not a develop branch - SKIPPING."'
                    }
                }
            }
        }
        stage ('Static analysis') {
            agent any //{ docker { image 'thearusable/nocturne:latest' } }
            steps {
                //cppcheck
		        sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
                publishCppcheck pattern:'cppcheck_report.xml'
		        
                //sh 'clang-tidy .'
            }
        }
        
        stage ('Build engine'){
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make all'
                    //sh 'make test'
                }
            }
        }

        stage ('Testing'){
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    //sh 'make all'
                    sh 'make test'
                }
            } 
        }
    }
    //post {
	//    always {
	//        
	//    }           
    //}
}
