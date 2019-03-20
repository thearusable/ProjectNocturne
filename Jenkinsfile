pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
        image = ''
    }

    agent any

    stages {

	    stage ('Build image') {
            steps{
                script {
                    // build image
                    image = docker.build registry

                    // only push docker image when build from develop branch
                    if (env.BRANCH_NAME == "develop"){
                        docker.withRegistry('', registryCredential) {
                            image.push("latest")
                        }
                    } else {
                        sh 'echo "Not a develop branch - SKIPPING."'
                    }
                }
            }
        }

        stage ('Pre-analysis') {
		    sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
        }
        
        stage ('Build'){
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
