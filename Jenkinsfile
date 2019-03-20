pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
        image = ''
    }

    //agent {
    //    dockerfile {
    //        filename 'Dockerfile'
    //    }
    //}

    agent any

    stages {

	    stage ('Building image') {
            steps{
                script {
                    image = docker.build registry
                }
            }
        }

        stage ('pre-analysis') {
            steps {
                sh 'echo "pre-analysis"'
		        //sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
            }
        }

        stage ('build'){
            steps {
                dir('build')
                {
                    sh 'echo "build"'
                    //sh 'cmake ..'
                    //sh 'make'
                }
            }
        }

        stage ('Publish image'){
            steps {
                script{
                    if (env.BRANCH_NAME == "feature/static_analysis"){
                        docker.withRegistry('', registryCredential) {
                            image.push("latest")
                        }
                    } else {
                        sh 'echo "Not a develop branch - SKIPPING."'
                    }
                }
            }

        //    steps {
        //        script {
                    //docker.withRegistry('', registryCredential)
                    //{
        //                sh 'docker push thearusable/nocturne'
                        //image.push("latest")
                    //}
        //        }
        //    }
        }
    }
    //post {
	//    always {
    //        script{
    //            sh 'docker push thearusable/nocturne'
    //        }
            //sh 'docker push thearusable/nocturne'
	        //publishCppcheck pattern:'cppcheck_report.xml'
	//    }           
   // }
}
