pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
        image = ''
    }

    agent {
        dockerfile {
            filename 'Dockerfile'
        }
    }

    stages {

	    //stage ('Building image') {
        //    steps{
        //        script {
        //            image = docker.build registry
        //        }
        //    }
        //}

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

            withDockerRegistry([ credentialsId: "dockerhub", url: "" ]) {
                // following commands will be executed within logged docker registry
                sh 'docker push $registry'
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
