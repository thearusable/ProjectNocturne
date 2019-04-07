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
                    docker.withRegistry( '', registryCredential ) {
                        sh 'docker push ${registry}:latest'
                    }
                    // only push docker image when build from develop branch
        //            if (env.BRANCH_NAME == "develop"){
        //                docker.withRegistry('', registryCredential) {
        //                    image.push("latest")
        //                }
        //            } else {
        //                sh 'echo "Not a develop branch - SKIPPING."'
        //            }
                }
            }
        }

        stage ('Pre-analysis') {
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
		        sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
            }
        }
        
        stage ('Build engine'){
            agent { docker { image 'thearusable/nocturne:latest' } }
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make'
                }
            }
        }
    }
    post {
	    always {
	        publishCppcheck pattern:'cppcheck_report.xml'
	    }           
    }
}
